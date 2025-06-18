#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"
#include "button.h"
#include "buzzer.h"

int melody[] = {
    DO, DO, DO, DO, DO,
    MI, SOL, SOL, MI, DO,
    SOL, SOL, MI, SOL, SOL, MI,
    DO, DO, DO
};

int noteDurations[] = {
    4, 8, 8, 4, 4,
    4, 8, 8, 4, 4,
    8, 8, 4, 8, 8, 4,
    4, 4, 2
};
int main(int argc, char** argv) {
	
    int fd = ledLibInit();
    
    if (fd < 0) {
        printf("failed open file\n");
        return 1;
    }
    printf("hihihihih\n");
  
        for (int i = 0; i<=7; i++) {
            ledOnOff(i,1);
            printf("LED %d ON\n", i + 1);
            sleep(1);
        }

        for (int i = 0; i<=7; i++) {
            ledOnOff(i,0);
            printf("LED %d OFF\n", i + 1);
            sleep(1);
        }
        printf("bye \n");
        ledLibExit();

    buzzerInit();

    for (int i = 0; i < 19; i++) {
        int durations = 1000 / noteDurations[i];
        buzzerTone(melody[i]);
        delay_ms(durations * 1.3);
        buzzerStop();
    }
    buzzerExit();
    BUTTON_MSG_T Data;
buttonInit();
int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);

while(1) {
//struct input_event stEvent;	
    int returnValue = 0;
    returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);
		
    if(Data.type== EV_KEY){
        printf("EV_KEY(");
        switch(Data.keyInput)
        {
            case KEY_VOLUMEUP: printf("Volume up key):"); break;
            case KEY_HOME: printf("Home key):"); break;
            case KEY_SEARCH: printf("Search key):"); break;
            case KEY_BACK: printf("Back key):"); break;
            case KEY_MENU: printf("Menu key):"); break;
            case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
        }
    if ( Data.pressed ) 
        printf("pressed\n");
    else 
        printf("released\n");
    } 
} 
    buttonExit();
}