#include <arpa/inet.h>      // sockaddr_in, htons(), htonl() 등 네트워크 관련
#include <stdio.h>          // printf(), perror()
#include <stdlib.h>         // exit(), malloc() 등
#include <string.h>         // memset()
#include <sys/socket.h>     // socket(), bind(), listen(), accept()
#include <unistd.h>         // close()

// 서버가 사용할 포트 번호
#define PORT 8080

// 한 번에 받을 최대 데이터 크기
#define BUFFER_SIZE 1024

int main(void)
{
    // 서버 소켓
    int server_fd;

    // 클라이언트와 연결된 소켓
    int client_fd;

    // 서버 주소 정보
    struct sockaddr_in server_addr;

    // 클라이언트 주소 정보
    struct sockaddr_in client_addr;

    // accept()에서 클라이언트 주소 크기를 저장할 변수
    socklen_t client_len = sizeof(client_addr);

    // 데이터를 받을 버퍼
    char buffer[BUFFER_SIZE];

    //-------------------------------------------------
    // 1. 소켓 생성
    //-------------------------------------------------

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
    {
        perror("socket");
        return 1;
    }

    //-------------------------------------------------
    // 2. 서버 주소 초기화
    //-------------------------------------------------

    // 구조체를 0으로 초기화
    memset(&server_addr, 0, sizeof(server_addr));

    // IPv4 사용
    server_addr.sin_family = AF_INET;

    // 사용할 포트 번호
    server_addr.sin_port = htons(PORT);

    // 모든 IP에서 접속 허용
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //-------------------------------------------------
    // 3. 소켓과 주소 연결(bind)
    //-------------------------------------------------

    if (bind(server_fd,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr)) == -1)
    {
        perror("bind");
        return 1;
    }

    //-------------------------------------------------
    // 4. 연결 요청 대기
    //-------------------------------------------------

    // 최대 5개의 연결 요청을 큐에 저장
    if (listen(server_fd, 5) == -1)
    {
        perror("listen");
        return 1;
    }

    printf("Server waiting...\n");

    //-------------------------------------------------
    // 5. 클라이언트 연결 수락
    //-------------------------------------------------

    // 여기서 클라이언트가 접속할 때까지 대기한다.
    client_fd = accept(server_fd,
                       (struct sockaddr *)&client_addr,
                       &client_len);

    printf("Client Connected!\n");

    //-------------------------------------------------
    // 6. 데이터 송수신
    //-------------------------------------------------

    while (1)
    {
        // 클라이언트로부터 데이터 받기
        int len = recv(client_fd,
                       buffer,
                       sizeof(buffer),
                       0);

        // 연결 종료
        if (len <= 0)
            break;

        // 받은 데이터를 그대로 다시 보냄(Echo)
        send(client_fd,
             buffer,
             len,
             0);
    }

    //-------------------------------------------------
    // 7. 소켓 종료
    //-------------------------------------------------

    close(client_fd);

    close(server_fd);

    return 0;
}