// fnd.c - FND 디스플레이 제어 라이브러리 구현

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "fnd.h"  // stFndWriteForm 정의 포함

#define FND_DRIVER_NAME "/dev/perifnd"

// 숫자(num)를 FND에 표시, dotflag는 각 자리 소수점 on/off 비트
int fndDisp(int num, int dotflag)
{
    int fd;
    int temp, i;
    stFndWriteForm stWriteData;

    // 1. dot 표시 여부 및 유효 자리 세팅
    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
        stWriteData.DataValid[i] = 1;
    }

   // 2. 숫자 6자리를 각 자리로 분할 저장
   temp = num % 1000000;
   stWriteData.DataNumeric[0] = temp / 100000;
   temp = num % 100000;
   stWriteData.DataNumeric[1] = temp / 10000;
   temp = num % 10000;
   stWriteData.DataNumeric[2] = temp / 1000;
   temp = num % 1000;
   stWriteData.DataNumeric[3] = temp / 100;
   temp = num % 100;
   stWriteData.DataNumeric[4] = temp / 10;
   stWriteData.DataNumeric[5] = num % 10;

   // 3. FND 디바이스 열기
   fd = open(FND_DRIVER_NAME, O_RDWR);
   if (fd < 0) {
       perror("driver open error");
       return 0;
   }

   // 4. FND에 데이터 쓰기
   write(fd, &stWriteData, sizeof(stFndWriteForm));

   // 5. 디바이스 닫기
   close(fd);

   return 1;
}
