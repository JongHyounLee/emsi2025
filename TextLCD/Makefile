all: main.elf
	scp main.elf ecube@192.168.175.233:/home/ecube/2025_project/sensors/TEXTLCD
	rm -f textlcd.o libMyPeri.a main.elf

textlcd.o:  textlcddrv.h textlcd.c  textlcd.h
	arm-linux-gnueabi-gcc -static -c textlcd.c -o textlcd.o

libMyPeri.a: textlcd.o textlcddrv.h textlcd.h
	arm-linux-gnueabi-ar rc libMyPeri.a textlcd.o

main.elf: main.c libMyPeri.a  textlcddrv.h textlcd.h
	arm-linux-gnueabi-gcc -static -o main.elf main.c -lMyPeri -L.


