#ifndef __FND_DRV_H__
#define __FND_DRV_H__
#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
typedef struct FNDWriteDataForm_tag
{
char DataNumeric[FND_DATA_BUFF_LEN]; //숫자 0-9
char DataDot[FND_DATA_BUFF_LEN]; //숫자 0 or 1
char DataValid[FND_DATA_BUFF_LEN]; //숫자 0 or 1
}stFndWriteForm,*pStFndWriteForm;
#endif// __FND_DRV_H__


int fndDisp(int num, int dotflag);

// 기능별 라이브러리 함수들
int fndStaticDisplay(int num);     // 정적 숫자 표시
int fndTimeDisplay();              // 현재 시간 표시 (HHMMSS)
int fndCountUp(int max);           // 0부터 max까지 1초 간격 카운트
int fndOff();  