all : main.elf
	scp main.elf ecube@192.168.50.76:/home/ecube/sensors/
	rm -f led.o libMyPeri.a main.elf

led.o : led.h led.c
	arm-linux-gnueabi-gcc -o led.o -c led.c 

fnd.o : fnd.h fnd.c
	arm-linux-gnueabi-gcc -o fnd.o -c fnd.c

libMyPeri.a : led.o fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o fnd.o

main.elf : main.c libMyPeri.a
	arm-linux-gnueabi-gcc -static -o main.elf main.c -l MyPeri -L. -lpthread
