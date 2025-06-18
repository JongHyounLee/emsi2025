all: main.elf
	scp main.elf ecube@192.168.50.211:/home/ecube
	rm -f $(OBJS) libMyPeri.a main.elf

CC      = arm-linux-gnueabi-gcc
AR      = arm-linux-gnueabi-ar
CFLAGS  = -static
OBJS    = led.o button.o buzzer.o fnd.o textlcd.o imu.o temp.o

libMyPeri.a: $(OBJS)
	$(AR) rc $@ $(OBJS)

main.elf: main.c libMyPeri.a
	$(CC) $(CFLAGS) -o $@ $< -l MyPeri -L. -lpthread

led.o: led.h led.c
	$(CC) $(CFLAGS) -c led.c -o $@

button.o: button.h button.c
	$(CC) $(CFLAGS) -c button.c -o $@
	echo "1. make button.o"

buzzer.o: buzzer.h buzzer.c
	$(CC) $(CFLAGS) -c buzzer.c -o $@
	echo "1. make buzzer.o"

fnd.o: fnd.h fnd.c
	$(CC) $(CFLAGS) -c fnd.c -o $@
	echo "1. make fnd.o"

textlcd.o: textlcddrv.h textlcd.h textlcd.c
	$(CC) $(CFLAGS) -c textlcd.c -o $@

imu.o: imu.h imu.c
	$(CC) $(CFLAGS) -c imu.c -o $@

temp.o: temp.h temp.c
	$(CC) $(CFLAGS) -c temp.c -o $@

clean:
	rm -f $(OBJS) libMyPeri.a main.elf

