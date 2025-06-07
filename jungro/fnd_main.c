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

int main() {
    fndStaticDisplay(123456);
    sleep(2);
    fndTimeDisplay();
    sleep(2);
    fndCountUp(10);
    fndOff();
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
                                                                         