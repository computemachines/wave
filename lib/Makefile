# (C) 2013 by Zack Smith.
# All rights reserved.

bmplib.a:
	gcc -Wall -c BMP.c font.c minifont.c
	ar rcs bmplib.a BMP.o font.o minifont.o

m:	main.c
	gcc -Wall BMP.c font.c minifont.c main.c -lm -o m

clean:
	rm -f BMP.o font.o minifont.o bmplib.a m m.exe
