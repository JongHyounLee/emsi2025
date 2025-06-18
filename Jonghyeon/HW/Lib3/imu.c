#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "imu.h"

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNEPATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"




void getAccel(int accel[]){
    // Accelerometer
    int fd = 0;
FILE *fp = NULL;
    fd = open(ACCELPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(ACCELPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &accel[0], &accel[1], &accel[2]);
    printf("Accel  : X = %4d, Y = %4d, Z = %4d\n", accel[0], accel[1], accel[2]);
    fclose(fp);
}

void getMagnet(int magnet[]){
    int fd = 0;
FILE *fp = NULL;
    // Magnetometer
    fd = open(MAGNEPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(MAGNEPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &magnet[0], &magnet[1], &magnet[2]);
    printf("Magnet : X = %4d, Y = %4d, Z = %4d\n", magnet[0], magnet[1], magnet[2]);
    fclose(fp);
}

void getGyro(int gyro[]){
    // Gyroscope
    int fd = 0;
FILE *fp = NULL;
    fd = open(GYROPATH "enable", O_WRONLY);
    dprintf(fd, "1");
    close(fd);

    fp = fopen(GYROPATH "data", "rt");
    fscanf(fp, "%d, %d, %d", &gyro[0], &gyro[1], &gyro[2]);
    fclose(fp);
    printf("I read Gyro : %d, %d, %d\r\n", gyro[0], gyro[1], gyro[2]);
}
