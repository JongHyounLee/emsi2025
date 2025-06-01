#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024] = {0};
    socklen_t client_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // 모든 IP에서 수신
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);

    printf("Waiting for message..\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        printf("connected to client!\n");

        while (1) {
            memset(buffer, 0, sizeof(buffer));
            int bytes_read = read(client_fd, buffer, sizeof(buffer));
            if (bytes_read <= 0) {
                printf("disconnected to client\n");
                break;
            }
            printf("Received message: %s\n", buffer);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}