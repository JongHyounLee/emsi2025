#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "server.h"
#include "buzzer.h"

#define PORT 8888

/*
typedef struct {
    int gameReady;
    int cursor;
    int buttonPressed;
} SOCKET_DATA; 
*/

/*
buttonPressed = -5
cursor = 0~8
*/
SOCKET_DATA socketData;
int data; 
pthread_t tid[0];
void *bgm_thread() {
    while(1) {
        superMario(400);
        sleep(5);
    }

}
int main() {
    buzzerInit();
    int sock = init_server(PORT);
    if (sock < 0) return -1;

    while (1) {
        int len = recv(sock, &(socketData.gameReady), sizeof(int), 0);
        if (socketData.gameReady == -1) {
            printf("received data : %d\n", socketData.gameReady);
            break;
        }
    }

    pthread_create(&tid[0], NULL, &bgm_thread, NULL);
    
    while(1) {
        int len = recv(sock, &(data), sizeof(int), 0);

        // when button preseed
        if (data == -5) {
            printf("buttonPressed!!!!\r\n");
        }
        
        //when cursor moved 
        else if (data >= 0 && data <= 8) {
            socketData.cursor = data;
            printf("cursorMoved : %d\r\n", data);
        }
        //sleep(1);
    }

    close(sock);
    return 0;
}