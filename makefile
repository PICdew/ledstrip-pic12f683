all: main

main: main.c
	sdcc -mpic14 -p12f683 main.c
 
upload: main
	pk2cmd -B/usr/share/pk2/ -PPIC12F683 -Fmain.hex -M -R -T

power: main
	pk2cmd -B/usr/share/pk2/ -PPIC12F683 -T

clean:
	rm *.asm *.cod *.hex *.lst *.o
