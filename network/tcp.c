#define _GNU_SOURCE

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <linux/if_ether.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BUFFER_SIZE 2048

/*
 * 가상 네트워크 인터페이스 설정
 *
 * TAP_IP:  우리 사용자 공간 스택의 IP
 * TAP_MAC: 우리 사용자 공간 스택의 MAC
 */
static const uint8_t TAP_MAC[ETH_ALEN] = {
    0x02, 0x00, 0x00, 0x00, 0x00, 0x04
};

/*
 * 네트워크 바이트 순서로 저장됩니다.
 * inet_pton()을 통해 런타임에 설정합니다.
 */
static uint32_t tap_ip;

/*
 * Ethernet 헤더
 *
 * Linux의 struct ethhdr를 사용해도 되지만,
 * 학습 목적으로 직접 선언했습니다.
 */
struct ethernet_header {
    uint8_t destination_mac[ETH_ALEN];
    uint8_t source_mac[ETH_ALEN];
    uint16_t ethertype;
} __attribute__((packed));

/*
 * Ethernet + IPv4 환경의 ARP 패킷
 */
struct arp_packet {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_length;
    uint8_t protocol_length;
    uint16_t opcode;

    uint8_t sender_mac[ETH_ALEN];
    uint32_t sender_ip;

    uint8_t target_mac[ETH_ALEN];
    uint32_t target_ip;
} __attribute__((packed));

static void print_mac(const uint8_t mac[ETH_ALEN])
{
    printf(
        "%02x:%02x:%02x:%02x:%02x:%02x",
        mac[0],
        mac[1],
        mac[2],
        mac[3],
        mac[4],
        mac[5]
    );
}

static void print_ipv4(uint32_t ip)
{
    char address[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &ip, address, sizeof(address)) == NULL) {
        printf("<invalid-ip>");
        return;
    }

    printf("%s", address);
}

/*
 * /dev/net/tun을 열고 TAP 인터페이스를 생성합니다.
 *
 * IFF_TAP:
 *   Ethernet 프레임(Layer 2)을 직접 읽고 씁니다.
 *
 * IFF_NO_PI:
 *   Linux가 추가하는 4바이트 packet information 헤더를 제거합니다.
 */
static int tap_alloc(char *device_name, size_t device_name_size)
{
    struct ifreq ifr;
    int fd;

    fd = open("/dev/net/tun", O_RDWR);

    if (fd < 0) {
        perror("open /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if (device_name[0] != '\0') {
        strncpy(ifr.ifr_name, device_name, IFNAMSIZ - 1);
        ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    }

    if (ioctl(fd, TUNSETIFF, &ifr) < 0) {
        perror("ioctl TUNSETIFF");
        close(fd);
        return -1;
    }

    snprintf(device_name, device_name_size, "%s", ifr.ifr_name);

    return fd;
}

static int send_arp_reply(
    int tap_fd,
    const struct ethernet_header *request_ethernet,
    const struct arp_packet *request_arp
)
{
    uint8_t buffer[
        sizeof(struct ethernet_header) +
        sizeof(struct arp_packet)
    ];

    struct ethernet_header *ethernet =
        (struct ethernet_header *)buffer;

    struct arp_packet *arp =
        (struct arp_packet *)(buffer + sizeof(*ethernet));

    memset(buffer, 0, sizeof(buffer));

    /*
     * Ethernet 응답:
     * 요청자의 MAC 주소로 전송
     */
    memcpy(
        ethernet->destination_mac,
        request_ethernet->source_mac,
        ETH_ALEN
    );

    memcpy(
        ethernet->source_mac,
        TAP_MAC,
        ETH_ALEN
    );

    ethernet->ethertype = htons(ETH_P_ARP);

    /*
     * ARP Reply 구성
     */
    arp->hardware_type = htons(ARPHRD_ETHER);
    arp->protocol_type = htons(ETH_P_IP);
    arp->hardware_length = ETH_ALEN;
    arp->protocol_length = sizeof(uint32_t);
    arp->opcode = htons(ARPOP_REPLY);

    /*
     * 우리 주소를 sender로 설정
     */
    memcpy(arp->sender_mac, TAP_MAC, ETH_ALEN);
    arp->sender_ip = tap_ip;

    /*
     * 요청자의 주소를 target으로 설정
     */
    memcpy(
        arp->target_mac,
        request_arp->sender_mac,
        ETH_ALEN
    );

    arp->target_ip = request_arp->sender_ip;

    ssize_t written = write(tap_fd, buffer, sizeof(buffer));

    if (written < 0) {
        perror("write TAP");
        return -1;
    }

    if ((size_t)written != sizeof(buffer)) {
        fprintf(
            stderr,
            "partial TAP write: %zd/%zu bytes\n",
            written,
            sizeof(buffer)
        );

        return -1;
    }

    printf("ARP reply: ");

    print_ipv4(arp->sender_ip);
    printf(" is at ");
    print_mac(arp->sender_mac);

    printf(" -> ");

    print_ipv4(arp->target_ip);
    printf("\n");

    return 0;
}

static void handle_arp(
    int tap_fd,
    const struct ethernet_header *ethernet,
    const uint8_t *payload,
    size_t payload_length
)
{
    if (payload_length < sizeof(struct arp_packet)) {
        fprintf(stderr, "ARP packet too short\n");
        return;
    }

    const struct arp_packet *arp =
        (const struct arp_packet *)payload;

    /*
     * Ethernet + IPv4 ARP인지 검사
     */
    if (ntohs(arp->hardware_type) != ARPHRD_ETHER) {
        return;
    }

    if (ntohs(arp->protocol_type) != ETH_P_IP) {
        return;
    }

    if (arp->hardware_length != ETH_ALEN) {
        return;
    }

    if (arp->protocol_length != sizeof(uint32_t)) {
        return;
    }

    uint16_t opcode = ntohs(arp->opcode);

    printf("ARP packet: opcode=%u sender=", opcode);

    print_ipv4(arp->sender_ip);
    printf(" [");
    print_mac(arp->sender_mac);
    printf("] target=");
    print_ipv4(arp->target_ip);
    printf("\n");

    /*
     * ARP Request가 아니면 응답하지 않습니다.
     */
    if (opcode != ARPOP_REQUEST) {
        return;
    }

    /*
     * 요청 대상 IP가 우리 IP인지 검사합니다.
     */
    if (arp->target_ip != tap_ip) {
        return;
    }

    send_arp_reply(tap_fd, ethernet, arp);
}

static void handle_ethernet_frame(
    int tap_fd,
    const uint8_t *buffer,
    size_t length
)
{
    if (length < sizeof(struct ethernet_header)) {
        fprintf(stderr, "Ethernet frame too short\n");
        return;
    }

    const struct ethernet_header *ethernet =
        (const struct ethernet_header *)buffer;

    uint16_t ethertype = ntohs(ethernet->ethertype);

    printf(
        "Ethernet frame: length=%zu type=0x%04x src=",
        length,
        ethertype
    );

    print_mac(ethernet->source_mac);
    printf(" dst=");
    print_mac(ethernet->destination_mac);
    printf("\n");

    const uint8_t *payload =
        buffer + sizeof(struct ethernet_header);

    size_t payload_length =
        length - sizeof(struct ethernet_header);

    switch (ethertype) {
        case ETH_P_ARP:
            handle_arp(
                tap_fd,
                ethernet,
                payload,
                payload_length
            );
            break;

        case ETH_P_IP:
            printf("IPv4 packet received; parser not implemented yet\n");
            break;

        default:
            printf("Unsupported EtherType: 0x%04x\n", ethertype);
            break;
    }
}

int main(void)
{
    char tap_name[IFNAMSIZ] = "tap0";
    uint8_t buffer[BUFFER_SIZE];

    if (inet_pton(AF_INET, "10.0.0.4", &tap_ip) != 1) {
        fprintf(stderr, "Failed to parse TAP IP\n");
        return EXIT_FAILURE;
    }

    int tap_fd = tap_alloc(tap_name, sizeof(tap_name));

    if (tap_fd < 0) {
        return EXIT_FAILURE;
    }

    printf("Created TAP interface: %s\n", tap_name);
    printf("Stack IP: 10.0.0.4\n");
    printf("Stack MAC: ");
    print_mac(TAP_MAC);
    printf("\n");

    printf("\nRun the following commands in another terminal:\n");
    printf("  sudo ip link set %s up\n", tap_name);
    printf("  sudo ip addr add 10.0.0.1/24 dev %s\n", tap_name);
    printf("  sudo arping -I %s 10.0.0.4\n\n", tap_name);

    while (1) {
        ssize_t bytes_read =
            read(tap_fd, buffer, sizeof(buffer));

        if (bytes_read < 0) {
            if (errno == EINTR) {
                continue;
            }

            perror("read TAP");
            break;
        }

        if (bytes_read == 0) {
            continue;
        }

        handle_ethernet_frame(
            tap_fd,
            buffer,
            (size_t)bytes_read
        );
    }

    close(tap_fd);

    return EXIT_SUCCESS;
}

//