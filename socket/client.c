#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define SERVER_ADDR "192.168.137.189"  // <- Kit2's server addr
int count = 0;
int main() {
    int sock;
    struct sockaddr_in server_addr;

    // message to send
    const char *messages[] = {"Tlqkf\n"};
    int num_messages = sizeof(messages) / sizeof(messages[0]);

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket failed");
        return 1;
    }

    // set server addr 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    // connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sock);
        return 1;
    }

    printf("Connected to Server! \n");

    // send message
    while (1) {
        for (int i = 0; i < num_messages; i++) {
            send(sock, messages[i], strlen(messages[i]), 0);
            printf("Send message: %s\n", messages[i]);
            sleep(1);  // 1초 대기
        }
    }

    close(sock);
    return 0;
}