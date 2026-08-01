#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //유닉스 계열 함수들

#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS FD_SETSIZE

int main(void) {
    int server_fd;
    int client_fd;
    int max_fd;

 struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    
}
