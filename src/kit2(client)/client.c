#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"


/*
    fail to coneect : reutrn -1
*/ 
int connect_server(char *SERVER_ADDRESS, int PORT) {
    int sock;
    struct sockaddr_in server_addr;

    // create socket 
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        perror("Creating Socket Failed\r\n");
        return -1;
    }

    // set server addr 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_ADDRESS, &server_addr.sin_addr);

    // connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sock);
        return -1;
    }

    printf("Connected to Server!\r\n");
    printf("IP Address : %s\r\n", SERVER_ADDRESS);
    return sock;
}