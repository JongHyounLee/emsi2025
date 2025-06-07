#include "MyGyro.h"

int main()
{
    GyroInit();
    pthread_join(GyroTh, NULL);
    Gyroexit();
    return 0;
}
