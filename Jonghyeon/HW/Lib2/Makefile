all: main.elf
	scp main.elf ecube@192.168.50.211:/home/ecube
	rm -f textlcd.o libMyPeri.a main.elf

textlcd.o:  textlcddrv.h textlcd.c  textlcd.h
	arm-linux-gnueabi-gcc -static -c textlcd.c -o textlcd.o

led.o : led.h led.c
	arm-linux-gnueabi-gcc -static -o led.o -c led.c 

button.o : button.h button.c
	arm-linux-gnueabi-gcc -static -c button.c -o button.o
	echo "1. make button.o"

buzzer.o : buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -static -o buzzer.o -c buzzer.c 
	echo "1. make buzzer.o"

fnd.o : fnd.h fnd.c
	arm-linux-gnueabi-gcc -static -o fnd.o -c fnd.c 
	echo "1. make fnd.o"

textlcd.o:  textlcddrv.h textlcd.c  textlcd.h
	arm-linux-gnueabi-gcc -static -c textlcd.c -o textlcd.o

libMyPeri.a: led.o button.o buzzer.o fnd.o textlcd.o 
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o fnd.o textlcd.o

main.elf: main.c libMyPeri.a 
	arm-linux-gnueabi-gcc -static -o main.elf main.c -l MyPeri -L. -lpthread
