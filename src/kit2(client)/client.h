#pragma once

typedef struct {
    int gameReady;
    int cursor;
    int buttonPressed;
} SOCKET_DATA;

extern SOCKET_DATA socketData;

int connect_server(char *SERVER_ADDRESS, int PORT);


