#include "MyAcc.h"

// 전역 변수 정의
static int fd = 0;
FILE *fp = NULL;
int accel[3];


void AccInit(void)
{
    fd = open(ACCELPATH "enable", O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dprintf(fd, "1");

    fp = fopen(ACCELPATH "data", "rt");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    pthread_create(&AccTh, NULL, Accread, NULL);
}

static void *Accread(void *arg)
{
    while (1)
    {
        fclose(fp);
        fp = fopen(ACCELPATH "data", "rt");
        if (fp == NULL) {
            perror("fopen");
            break;
        }
        fscanf(fp,"%d, %d, %d",&accel[0],&accel[1],&accel[2]);
        printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
        usleep(100000);
    }
    return NULL;
}

void Accexit(void)
{
    close(fd);
    fclose(fp);
}

