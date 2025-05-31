#ifndef MYGYRO_H
#define MYGYRO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
pthread_t GyroTh;
// 센서 경로
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"
// 함수 선언 (필요하면)
void GyroInit(void);
static void *Gyroread(void *arg);
void Gyroexit(void);

#endif
