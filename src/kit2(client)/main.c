#include "socket.h"
#include "button.h"
#include "buzzer.h"
#include "gyro.h"
#include <pthread.h>

#define PORT 8888
#define SERVER "192.168.137.1"

int gyro[3];
int sock;
SOCKET_DATA socketData;

void *readChange(void *arg)
{
    while(1) {
        //printf("side%d\n",change);
        if(move)
        {
            buzzerTone(DO);
            delay_ms(100);
            buzzerStop();
            send(sock, &(socketData.cursor), sizeof(int), NULL);
            printf("move to : %d, buttonPressed : %d\r\n", socketData.cursor, socketData.buttonPressed);
            #ifdef MUTEX_ENABLE
            pthread_mutex_lock(&lock);
            #endif
            move=0;
            #ifdef MUTEX_ENABLE
            pthread_mutex_unlock(&lock);
            #endif
        }
    }

}



void initSensors() {
    buttonInit();
    buzzerInit();
}

int main() {
    BUTTON_MSG_T Data;
    initSensors();
    int prev_pressed = 0;
    int prev_key = -1;
    int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
    socketData.cursor = 4;
    sock = connect_server(SERVER, PORT);
    if (sock == -1)
      return 0;

    // sending gameReady
    printf("press Any Key to start\r\n");
    while(1) {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);
  
        if(Data.type == EV_KEY){
            if (Data.pressed && !(prev_pressed && prev_key == Data.keyInput)) {
                send(sock, &(socketData.gameReady), sizeof(int), NULL);
                printf("send GameReady : %d\r\n", socketData.gameReady);
                break;
            }
        }
    }   
    
    pthread_create(&Buzz,NULL,readChange,NULL);
    GyroInit();

    while(1) {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);
  
        if(Data.type == EV_KEY){
            if (Data.keyInput == KEY_HOME) {
                if (Data.pressed && !(prev_pressed && prev_key == KEY_HOME)) {
                    socketData.buttonPressed = 1;
                    send(sock, &(socketData.buttonPressed), sizeof(int), NULL);
                    printf("send : %d, buttonPressed : %d \r\n", socketData.cursor, socketData.buttonPressed);
                    socketData.buttonPressed = 0;
                    buzzerTone(DO);
                    delay_ms(50);
                    buzzerStop();
                }
            }
        }
    }

    buttonExit();
    buzzerExit();
    close(sock);

    printf("main done\r\n");
    return 0;
}