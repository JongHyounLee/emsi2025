all : MyGyro.elf
	scp MyGyro.elf ecube@192.168.50.211:/home/ecube


MyGyro.o:
	arm-linux-gnueabi-gcc -I. -c MyGyro.c -o MyGyro.o
libMyPeri.a:
	arm-linux-gnueabi-ar rc libMyPeri.a MyGyro.o

MyGyro.elf:MyGyro.o libMyPeri.a
	arm-linux-gnueabi-gcc -I. -o MyGyro.elf main.c -l MyPeri -L. -lpthread

clean:
	rm -rf *.elf *.o *.a
