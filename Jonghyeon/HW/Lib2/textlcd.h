#ifndef _TLCD_H_
#define _TLCD_H_
#define LED_DRIVER_NAME

#define TEXTLCD_DRIVER_NAME     "/dev/peritextlcd"

void doHelp(void);
int TlcdLibInit();
int lcdtextwrite(const char *str, int lineFlag);

int TlcdLibExit();


#endif //_TLCD_H_
