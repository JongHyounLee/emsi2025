all : main.elf
	scp main.elf ecube@192.168.137.54:/home/ecube/src/src/client
	echo "[send main.elf]"
	rm -f *.o *.elf
	echo "[remove files]"

button.o : button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
	echo "1. make button.o"

buzzer.o : buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
	echo "2. make buzzer.o"

gyro.o : gyro.h gyro.c 
	arm-linux-gnueabi-gcc -c gyro.c -o gyro.o
	echo "3. make gyro.o"

client.o : client.h client.c 
	arm-linux-gnueabi-gcc -c client.c -o client.o
	echo "4. make client.o"
	
libMyPeri.a : button.o buzzer.o gyro.o client.o
	arm-linux-gnueabi-ar rc libMyPeri.a button.o buzzer.o gyro.o client.o
	echo "[make libMyPeri.a]"

main.elf : main.c libMyPeri.a
	arm-linux-gnueabi-gcc -o main.elf main.c -l MyPeri -L. -lpthread
	echo "[make main.elf]"