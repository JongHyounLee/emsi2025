all : main.elf
	scp main.elf ecube@192.168.137.80:/home/ecube/jw_serverTest
	echo "[send main.elf]"
	rm -f *.o *.elf
	echo "[remove files]"

buzzer.o : buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	echo "2. make buzzer.o"

server.o : server.h server.c 
	arm-linux-gnueabi-gcc -c server.c -o server.o
	echo "4. make server.o"
	
libMyPeri.a : server.o buzzer.o 
	arm-linux-gnueabi-ar rc libMyPeri.a buzzer.o server.o
	echo "[make libMyPeri.a]"

main.elf : main.c libMyPeri.a  
	arm-linux-gnueabi-gcc -o main.elf main.c -l MyPeri -L. -lpthread 
	echo "[make main.elf]"