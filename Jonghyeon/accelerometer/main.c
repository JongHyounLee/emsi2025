#include "MyAcc.h"

int main()
{
    AccInit();
    pthread_join(AccTh, NULL);
    Accexit();
    return 0;
}
