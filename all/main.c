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
#include "fnd.h"
#include "textlcddrv.h"
#include "textlcd.h"

//buzzer; gomsemali
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



int main(){

    printf("device init start\n");
    int fd = TlcdLibInit();
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
    printf("text lcd init done\n");
    

    //init led
    int fd_led = ledLibInit();
    if (fd_led < 0) {
        printf("failed open LED file\n");
        return 1;
    } 
    printf("led  init done\n");


    //init button & message queue
    BUTTON_MSG_T Data;
    buttonInit();
    int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);    
    printf("button init done\n");

    //init buzzer & fnd(none)
    buzzerInit();
    printf("buzzer init done\n");

    //textLCD
    lcdtextwrite("hello", 1);
    lcdtextwrite("device init done\n", 2);
    

    //led
        
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
    
    //fnd
        fndTimer(10, DOWNCOUNT);
    
    //buzzer
    for (int i = 0; i < 19; i++) {
        int durations = 1000 / noteDurations[i];
        buzzerTone(melody[i]);
        delay_ms(durations * 1.3);
        buzzerStop();
    }

}   
