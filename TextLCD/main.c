#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcddrv.h"
#include "textlcd.h"


#define TEXT1 "hello!"
#define TEXT2 "emsi ^_^ &#$!"
#define TEXT3 "OK....."
#define TEXT4 "g o o d"
#define LINE 1  // 1 or 1


int main(int argc , char **argv)
{
	
	int fd = TlcdLibInit();
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	
	while(1){
		lcdtextwrite(TEXT1, 1);
		sleep(1);
		lcdtextwrite(TEXT2, 2);
		sleep(1);
		lcdtextwrite(TEXT3, 1);
		sleep(1);
		lcdtextwrite(TEXT4, 2);
		sleep(1);
	}
	
	TlcdLibExit();
	return 0;

}
