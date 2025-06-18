#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "textlcd.h"
#include "textlcddrv.h"
#include "imu.h"
#include "temp.h"

/* ───── BUZZER 악보 (사용 시 활성화) ───── */
static const int melody[] = {
    DO, DO, DO, DO, DO,
    MI, SOL, SOL, MI, DO,
    SOL, SOL, MI, SOL, SOL, MI,
    DO, DO, DO
};
static const int noteDur[] = {
    4, 8, 8, 4, 4,
    4, 8, 8, 4, 4,
    8, 8, 4, 8, 8, 4,
    4, 4, 2
};
/* ─────────────────────────────── */

int main(void)
{
	int fd = TlcdLibInit();
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
    lcdtextwrite("Init devices...\n", 1);
    if (ledLibInit() < 0) {
        perror("ledLibInit");
        return EXIT_FAILURE;
    }

    if (buttonInit() == 0) {
        fprintf(stderr, "buttonInit failed\n");
        return EXIT_FAILURE;
    }

buzzerInit();

    fndTimer(10, DOWNCOUNT);

    /* ───── 센서 읽기 ───── */
    int accel[3] = {0}, magnet[3] = {0}, gyro[3] = {0};
    getAccel(accel);
    getMagnet(magnet);
    getGyro(gyro);

   temp_read();

    /* ───── LCD 출력 ───── */
/* ───── Text LCD : 두 줄만 출력 ───── */
lcdtextwrite("hello", 1);           // 1행
lcdtextwrite("LCD init done", 2); // 2행

    /* ───── LED 시퀀스 ───── */
    for (int i = 0; i < 8; i++) { ledOnOff(i, 1); sleep(1); }
    for (int i = 0; i < 8; i++) { ledOnOff(i, 0); sleep(1); }

    /* ───── 버저 멜로디 ───── */
    /*
    for (size_t i = 0; i < sizeof(melody)/sizeof(melody[0]); i++) {
        int ms = 1000 / noteDur[i];
        buzzerTone(melody[i]);
        delay_ms((int)(ms * 1.3));
        buzzerStop();
    }
    */

    /* ───── 종료 정리 ───── */
    buzzerExit();
    ledLibExit();
    buttonExit();
    // TlcdLibExit();  // 구현된 경우에만 호출

    return EXIT_SUCCESS;
}
