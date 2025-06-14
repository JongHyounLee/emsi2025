#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

void buzzerEnable(int bEnable) {
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    int fd = open(path, O_WRONLY);
    if (bEnable == 1)
        write(fd, &"1", 1);
    else
        write(fd, &"0", 1);
}

void setFrequency(int frequency) {
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    int fd = open(path, O_WRONLY);
    dprintf(fd, "%d", frequency);
    close(fd);
}

void buzzerInit() {
    //Fine Buzzer System Path
    DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL) {
        while(1) {
            struct dirent *dir_entry;
            dir_entry = readdir(dir_info);
            if (dir_entry == NULL) break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0) {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir, "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name );
            }
        }
    }

    printf("find %s\n", gBuzzerBaseSysDir);


    return ifNotFound;
}

void buzzerExit() {
    buzzerEnable(0);
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    close(path);
}
void buzzerTone(int scale) {
    setFrequency(scale);
    buzzerEnable(1);
}
void buzzerStop() {
    buzzerEnable(0);
}

void delay_ms(unsigned int milliseconds) {
    usleep(milliseconds * 1000);  
}

void superMario(int tempo) {
    int melody[] = {
      NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
      NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
      NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
      NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
      NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
      REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
      NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
      NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
      NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
      REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
    
      
      REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
      REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
      REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
      NOTE_C5,2, REST,2,
    
      REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
      REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
      REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
      NOTE_C5,2, REST,2,
    
      NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
    
      NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
      REST,1, 
      NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
      NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
      NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
      NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
      
      NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
      NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
      REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
    
      NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
      NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
      NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
      REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
    
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
      
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
      NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
    
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
      
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
      NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
      NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
      REST,1,
    
      NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
      NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
      NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
      
      NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
      NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
      NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
      NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
      NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
      
      //game over sound
      NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
      NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
      NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
    
    };
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  
    buzzerInit();
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
  
      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } 
      else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
  
      buzzerTone(melody[thisNote]);
      delay_ms(noteDuration * 0.9);
      buzzerStop();
      delay_ms(noteDuration);
  
    }
    buzzerExit();
  }