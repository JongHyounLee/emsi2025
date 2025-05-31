// file: main.c
// 간단한 FND 제어 테스트용 프로그램
// 사용법:
//   fndtest s <숫자6자리이내>       : 숫자를 고정으로 표시
//   fndtest t                      : 현재 시간을 HHMMSS 형태로 표시
//   fndtest c <최대값>             : 0부터 <최대값>까지 1초 간격으로 카운트하여 표시
//   fndtest o                      : FND 모두 끔 (0으로 표시)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fnd.h"   // stFndWriteForm 정의와 fndDisp 선언이 포함되어야 함

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  %s s <number>    : static display (0 ~ 999999)\n", argv[0]);
        printf("  %s t             : time display (HHMMSS)\n", argv[0]);
        printf("  %s c <max>       : count up from 0 to <max> (1초 간격)\n", argv[0]);
        printf("  %s o             : turn FND off (display 0)\n", argv[0]);
        return 0;
    }

    char mode = argv[1][0];
    int result = 0;

    if (mode == 's') {
        // static display: argv[2]번 숫자를 표시
        if (argc < 3) {
            fprintf(stderr, "Error: s 모드에는 숫자를 인수로 입력해야 합니다.\n");
            return 1;
        }
        int num = atoi(argv[2]);
        if (num < 0 || num > 999999) {
            fprintf(stderr, "Error: 숫자는 0 ~ 999999 범위여야 합니다.\n");
            return 1;
        }
        result = fndDisp(num, 0);   // dotflag = 0 (소수점 없음)
        if (!result) {
            perror("driver open error");
            return 1;
        }
        printf("Static display: %06d\n", num);

    } else if (mode == 't') {
        // time display: 현재 시간을 HHMMSS 형태로 표시
        time_t     now;
        struct tm *tm_now;
        now = time(NULL);
        tm_now = localtime(&now);
        int hh = tm_now->tm_hour;
        int mm = tm_now->tm_min;
        int ss = tm_now->tm_sec;
        int display_num = hh * 10000 + mm * 100 + ss;
        result = fndDisp(display_num, 0);
        if (!result) {
            perror("driver open error");
            return 1;
        }
        printf("Time display: %02d:%02d:%02d → %06d\n", hh, mm, ss, display_num);

    } else if (mode == 'c') {
        // count display: 0부터 argv[2]까지 1초 간격으로 표시
        if (argc < 3) {
            fprintf(stderr, "Error: c 모드에는 최대값을 인수로 입력해야 합니다.\n");
            return 1;
        }
        int max_count = atoi(argv[2]);
        if (max_count < 0 || max_count > 999999) {
            fprintf(stderr, "Error: 최대값은 0 ~ 999999 범위여야 합니다.\n");
            return 1;
        }
        for (int i = 0; i <= max_count; i++) {
            result = fndDisp(i, 0);
            if (!result) {
                perror("driver open error");
                return 1;
            }
            printf("Count: %06d\r", i);
            fflush(stdout);
            sleep(1);
        }
        printf("\n");

    } else if (mode == 'o') {
        // off: 0으로 표시 (사실상 000000)
        result = fndDisp(0, 0);
        if (!result) {
            perror("driver open error");
            return 1;
        }
        printf("FND OFF (000000)\n");

    } else {
        fprintf(stderr, "Error: 알 수 없는 모드 '%c'\n", mode);
        return 1;
    }

    return 0;
}

~                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
~                                                                         