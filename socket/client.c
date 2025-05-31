// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define SERVER_ADDR "192.168.XXX.XXX"
int main() {
    int sock;
    struct sockaddr_in server_addr;
    char *message = "hello world";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // 여기에 키트2의 IP 주소를 넣어야 함
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    send(sock, message, strlen(message), 0);

    printf("메시지 전송 완료\n");
    close(sock);

    return 0;
}