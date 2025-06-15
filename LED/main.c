
//1. 처음 random한 4구역에 불 생성
//2. 불을 끄면 해당 fire array에 '0'  &  끈 시간에 따라 점수 차등 부여 (금방 끄면 +5점, 늦으면 +1점 등)
//3. 만약 불을 못 끄고 5초가 지나면 fire array '0'  &  점수 -5 점
//4. 4초에 한 번 불이 없는 fire array 하나에 새로운 불 생성 

// main문 : scanf로 'cursor'변수 값, 'water'변수 1 을 차례로 받아 thread로 전달
//          (sursor, water 변수 kit2에서 받는거 구현되면 삭제 필요)




#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "fnd.h"
#include "led.h"

#define NEW_FIRE_TIMER 3

volatile  unsigned int fire[9];
volatile unsigned int cursor = 0; // 0~8
volatile static unsigned int gameReady;
volatile  unsigned int water;

volatile unsigned int life = 8;
volatile unsigned int dead = 0;
int new_fire_timer = -1;

volatile static unsigned int score = 0;
volatile static unsigned int timer[9] = {0,0,0,0,0,0,0,0,0}; // timer 초기화

pthread_t tid[4];
pthread_mutex_t lock;


void* fire_array(void *arg) { //fire array thread
    
    int random_index;
    
    pthread_mutex_lock(&lock);
    
        random_index = rand()%9;
        fire[random_index] = 1;
        timer[random_index] = -1;

    pthread_mutex_unlock(&lock);
    
    while(!dead){
        if(water) { //물을 발사 했는데
            water = 0;
            pthread_mutex_lock(&lock); //mutex lock

	printf("[DEBUG] cursor=%d, fire=%d, timer=%d\n", cursor, fire[cursor], timer[cursor]); // for debugging

            if(fire[cursor]){ //해당 위치에 불이 있으면
                fire[cursor] = 0; // 불 배열을 0으
		int delta = 6 - timer[cursor];
		printf("[DEBUG] score += %d\n", delta);
				  //
                score += delta;// 점수를 1 올림
	        new_fire_timer = NEW_FIRE_TIMER-1;
	    }
            pthread_mutex_unlock(&lock);  //mutex unlock
        }
    }
    return 0;
}

void* fire_timer(void *arg) {
   
    
    int new_fire_index;
    
    while(!dead){
        usleep(1000 * 1000); //1초 delay
        
         pthread_mutex_lock(&lock); //mutex lock
        
        new_fire_timer = new_fire_timer + 1; //4초에 한 번 새로운 fire 생성
        
        for(int i = 0; i<9; i++){
            if(fire[i])//불이 있는 위치의 index면
                timer[i] = timer[i] + 1; //해당 위치 fire의 timer +1
            else //불이 없는 위치면 (불이 중간에 꺼졌으면)
                timer[i] = 0; //timer 초기화
                
            if(timer[i] == NEW_FIRE_TIMER){ // 만약 증가 시킨 값이 5면 (time out)
                fire[i] = 0; // 불 배열을 0으로 만들고
                score = score - 5; // 점수를 5 깎고
                life = life - 1;
		if(life == 0){
                    dead = 1;
                    printf("\n\n**** YOU DEAD *****(dead flag : %d)\n", dead);
                }
		//timer[i] = 0; //timer 초기화
            }
        }
        
        if(new_fire_timer == NEW_FIRE_TIMER) {// 4초에 한 번 새로운 fire 생성
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

void* fnd_display(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);       // score 보호
        int temp_score = score;          // 복사해서 표시
        pthread_mutex_unlock(&lock);
        /*
	int is_negative = 0;
        if (temp_score < 0) {
		is_negative = 1;
		temp_score = -temp_score;
	}
        */
        fndInit(temp_score, 0);  // dotflag=0
        
        usleep(300 * 1000);  // 300ms 간격으로 갱신
    }
    return NULL;
}

void* led_life(void *arg) {
	while (1) {
		pthread_mutex_lock(&lock);
		int temp_life = life;
		pthread_mutex_unlock(&lock);
		
		for (int i = 0; i < 8; i++) {
            		if (i < temp_life) ledOnOff(i, 1);  // ON
            		else ledOnOff(i, 0);  // OFF
        	}

        	usleep(300 * 1000);  // 0.1초 주기
	}
	return NULL;
}



int main(void)
{
    int i=0;
    int err0;
    int err1;
    int err2;
    int err3;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf ("\n Mutex Init Failed!!\n");
        return 1;
    }
    
    err0 = pthread_create(&(tid[0]), NULL,&fire_array, NULL);
    err1 = pthread_create(&(tid[1]), NULL,&fire_timer, NULL);
    err2 = pthread_create(&(tid[2]), NULL,&fnd_display, NULL);
    err3 = pthread_create(&(tid[3]), NULL,&led_life, NULL);

    if (err0 != 0 | err1 != 0 | err2 != 0 | err3 != 0 )
        printf ("Thread Create Error: \n");
 
   ledLibInit();
   for (int i = 0; i < 8; i++) {
    ledOnOff(i, 1);
   }


    while(1){
        scanf("%d", &cursor);
        printf("cursor index :  %d \n", cursor);
        scanf("%d", &water);
        printf("water index :  %d \n", water);
    }
    
    pthread_join (tid[0], NULL);
    pthread_join (tid[1], NULL);
    pthread_join (tid[2], NULL);
    pthread_join (tid[3], NULL);
    return 0;
    }
