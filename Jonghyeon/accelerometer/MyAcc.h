#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
pthread_t AccTh;

void AccInit(void);
static void *Accread(void *arg);
void Accexit(void);