all: main

main: main.c
	sdcc --use-non-free -mpic14 -p12f1572 main.c

upload: main
	pk2cmd -B/usr/share/pk2/ -PPIC12F1572 -Fmain.hex -M -R -T

power: main
	pk2cmd -B/usr/share/pk2/ -PPIC12F1572 -T

clean:
	rm *.asm *.cod *.hex *.lst *.o
