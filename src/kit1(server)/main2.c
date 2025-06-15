//1. 처음 random한 4구역에 불 생성
//2. 불을 끄면 해당 fire array에 '0'  &  끈 시간에 따라 점수 차등 부여 (금방 끄면 +5점, 늦으면 +1점 등)
//3. 만약 불을 못 끄고 5초가 지나면 fire array '0'  &  점수 -5 점
//4. 4초에 한 번 불이 없는 fire array 하나에 새로운 불 생성 

// main문 : scanf로 'cursor'변수 값, 'water'변수 1 을 차례로 받아 thread로 전달
//          (sursor, water 변수 kit2에서 받는거 구현되면 삭제 필요)


// main.c 파일이랑 통합해야 함. 

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "textlcddrv.h"
#include "textlcd.h"
#include "server.h"
#include "colorLED.h"
volatile static unsigned int fire[9];
volatile static unsigned int cursor = 0; // 0~8
volatile static unsigned int gameReady;
volatile static unsigned int water;

volatile static unsigned int score = 0;
volatile static unsigned int timer[9] = {0,0,0,0,0,0,0,0,0}; // timer 초기화

pthread_t tid[3];
// pthread_t Textlcd_th;

pthread_mutex_t lock;

#define TEXT1 "progression rate"
#define TEXT2 "go@          end"
#define TEXT3 "go@@         end"
#define TEXT4 "go@@@        end"
#define TEXT5 "go@@@@       end"
#define TEXT6 "go@@@@@      end"
#define TEXT7 "go@@@@@@     end"
#define TEXT8 "go@@@@@@@    end"
#define TEXT9 "go@@@@@@@@   end"
#define TEXT10 "go@@@@@@@@@  end"
#define TEXT11 "go@@@@@@@@@@ end"
#define TEXT12 "go@@@@@@@@@@@end"
#define LINE 1  // 1 or 1


void PlayTime(void *arg)
{
    int fd = TlcdLibInit();
   if ( fd < 0 )
   {
      perror("driver (//dev//peritextlcd) open error.\n");
      return 1;
   }
    while(1){
      lcdtextwrite(TEXT1, 1);
      sleep(1);
      lcdtextwrite(TEXT2, 2);
      sleep(10);
        lcdtextwrite(TEXT3, 2);
      sleep(10);
        lcdtextwrite(TEXT4, 2);
      sleep(10);
        lcdtextwrite(TEXT5, 2);
      sleep(10);
        lcdtextwrite(TEXT6, 2);
      sleep(10);
        lcdtextwrite(TEXT7, 2);
      sleep(10);
        lcdtextwrite(TEXT8, 2);
      sleep(10);
      lcdtextwrite(TEXT9, 2);
      sleep(10);
      lcdtextwrite(TEXT10, 2);
      sleep(10);
        lcdtextwrite(TEXT11, 2);
      sleep(10);
        lcdtextwrite(TEXT12, 2);
      sleep(10);

   }
   
   TlcdLibExit();
   return 0;

}
void *ColorLed(void *arg)
{
    colorLED_init();
    while(1)
    {
        /* ── 빨간색 ON ─────────────────── */
        colorLED_serPercent(100, 0);   // R 100 %
        colorLED_serPercent(0,   1);   // G  0 %
        colorLED_serPercent(0,   2);   // B  0 %
        colorLED_pwmEnable();          // 전체 PWM 갱신
        delay_ms(500);

                /* ── 파란색 ON ─────────────────── */
        colorLED_serPercent(0,   0);   // R  0 %
        colorLED_serPercent(100,   1);   // G  0 %
        colorLED_serPercent(0, 2);   // B 100 %
        colorLED_pwmEnable();
        delay_ms(200);
        /* ── 파란색 ON ─────────────────── */
        colorLED_serPercent(0,   0);   // R  0 %
        colorLED_serPercent(0,   1);   // G  0 %
        colorLED_serPercent(100, 2);   // B 100 %
        colorLED_pwmEnable();
        delay_ms(500);
    }
}

void* fire_array(void *arg) { //fire array thread
    
    int random_index;
    
    pthread_mutex_lock(&lock);
    
    for(int i = 0; i<4; i++){ //초반 fire 4개 random 초기화
        random_index = rand()%9;
        while(fire[random_index]){
            random_index = rand()%9;
        }
        fire[random_index] = 1;
    }
    
    pthread_mutex_unlock(&lock);
    
    while(1){
        if(water) { //물을 발사 했는데
            water = 0;
            pthread_mutex_lock(&lock); //mutex lock

            if(fire[cursor]) //해당 위치에 불이 있으면
                fire[cursor] = 0; // 불 배열을 0으로 만들고
                score = score + (6-timer[cursor]);// 점수를 1 올림
                
            pthread_mutex_unlock(&lock);  //mutex unlock
        }
    }
    return 0;
}

void* fire_timer(void *arg) {
    
    int new_fire_timer = 0;
    int new_fire_index;
    
    while(1){
        usleep(1000 * 1000); //1초 delay
        
         pthread_mutex_lock(&lock); //mutex lock
        
        new_fire_timer = new_fire_timer + 1; //4초에 한 번 새로운 fire 생성
        
        for(int i = 0; i<9; i++){
            if(fire[i])//불이 있는 위치의 index면
                timer[i] = timer[i] + 1; //해당 위치 fire의 timer +1
            else //불이 없는 위치면 (불이 중간에 꺼졌으면)
                timer[i] = 0; //timer 초기화
                
            if(timer[i] == 5){ // 만약 증가 시킨 값이 5면 (time out)
                fire[i] = 0; // 불 배열을 0으로 만들고
                score = score - 5; // 점수를 5 깎고
                //timer[i] = 0; //timer 초기화
            }
        }
        
        if(new_fire_timer == 4) {// 4초에 한 번 새로운 fire 생성
            new_fire_timer = 0;
            new_fire_index = rand()%9; //0~8 난수 생성 (초기값 생성)
            while(fire[new_fire_index]) // 생성된 난수의 값에 이미 불이 있으면
                new_fire_index = rand()%9; //새로운 난수 생성
                
            fire[new_fire_index] = 1; //새로운  불을 배열에 넣고
            timer[new_fire_index] = 0; //해당 불 timer 초기화
        }
        
        printf("*FIRE*  : %d %d %d %d %d %d %d %d %d", fire[0],fire[1],fire[2],fire[3],fire[4],fire[5],fire[6],fire[7],fire[8]);
        printf("        *TIMER* : %d %d %d %d %d %d %d %d %d", timer[0],timer[1],timer[2],timer[3],timer[4],timer[5],timer[6],timer[7],timer[8]);
        printf("        *NEW_FIRE_TIMER : %d ", new_fire_timer);
        printf("        *SCORE : %d \n", score);
        
         pthread_mutex_unlock(&lock);  //mutex unlock
        
    }
}


int main(void)
{
    int i=0;
    int err0, err1, err2, err3;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf ("\n Mutex Init Failed!!\n");
        return 1;
    }
    
    err0 = pthread_create(&(tid[0]), NULL,&fire_array, NULL);
    err1 = pthread_create(&(tid[1]), NULL,&fire_timer, NULL);
    err2 = pthread_create(&(tid[2]), NULL,&PlayTime, NULL);
    err3 = pthread_create(&(tid[3]), NULL,&ColorLed, NULL);
    //err2 = pthread_create(&(tid[2]), NULL,&read_data_forTEST, NULL);
    
    if (err0 != 0 | err1 != 0)
        printf ("Thread Create Error: \n");
        
    while(1){
        scanf("%d", &water);
        printf("water index : %d\n", water);
        scanf("%d", &cursor);
        printf("water index : %d\n", cursor);

    }
    
    pthread_join (tid[0], NULL);
    pthread_join (tid[1], NULL);
    //pthread_join (tid[2], NULL);
    return 0;
    }

