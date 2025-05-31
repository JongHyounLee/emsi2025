#include "MyGyro.h"

// 전역 변수 정의
int fd = 0;
FILE *fp = NULL;
int gyro[3];
pthread_t GyroTh;

void GyroInit(void)
{
    fd = open(GYROPATH "enable", O_WRONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    dprintf(fd, "1");

    fp = fopen(GYROPATH "data", "rt");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    pthread_create(&GyroTh, NULL, Gyroread, NULL);
}

static void *Gyroread(void *arg)
{
    while (1)
    {
        fclose(fp);
        fp = fopen(GYROPATH "data", "rt");
        if (fp == NULL) {
            perror("fopen");
            break;
        }
        fscanf(fp, "%d, %d, %d", &gyro[0], &gyro[1], &gyro[2]);
        printf("I read Gyroscope: %d, %d, %d\n", gyro[0], gyro[1], gyro[2]);
        usleep(100000);
    }
    return NULL;
}

void Gyroexit(void)
{
    close(fd);
    fclose(fp);
}

