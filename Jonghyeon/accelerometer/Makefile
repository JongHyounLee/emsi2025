all : MyAcc.elf
	scp MyAcc.elf ecube@192.168.50.211:/home/ecube
MyAcc.o:
	arm-linux-gnueabi-gcc -I. -c MyAcc.c -o MyAcc.o
libMyPeri.a:
	arm-linux-gnueabi-ar rc libMyPeri.a MyAcc.o

MyAcc.elf:MyAcc.o libMyPeri.a
	arm-linux-gnueabi-gcc -I. -o MyAcc.elf main.c -l MyPeri -L. -lpthread

clean:
	rm -rf *.elf *.o *.a
