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
#include "MyGyro.h"
//buzzer; gomsemali
int move = 0;
pthread_t move_interrupt;
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

pthread_mutex_t lock;

int move_catch(void)
{

    while(1)
    {
    if(move)
    {
        for (int i = 0; i < 1; i++) 
        {
            int durations = 1000 / noteDurations[i];
            buzzerTone(melody[i]);
            delay_ms(durations * 1.3);
            buzzerStop();
        }
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

int main(){
while(1)
{
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

    GyroInit();//Gyro read
    pthread_create(&move_interrupt, NULL, move_catch, NULL);
    pthread_join(GyroTh, NULL);
    while(1);
}
}   
