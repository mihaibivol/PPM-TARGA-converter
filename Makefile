CC=gcc
CFLAGS=-Wall

convert: obj/main.o obj/convert.o obj/tga.o obj/ppm.o obj/image.o
	$(CC) $(CFLAGS) obj/main.o obj/convert.o obj/tga.o obj/ppm.o obj/image.o -o convert


obj/image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c -o obj/image.o

ppm.h: image.h

tga.h: image.h

obj/ppm.o: ppm.c ppm.h 
	$(CC) $(CFLAGS) -c ppm.c -o obj/ppm.o

obj/tga.o: tga.c tga.h 
	$(CC) $(CFLAGS) -c tga.c -o obj/tga.o

convert.h: ppm.h tga.h

obj/convert.o: convert.c convert.h 
	$(CC) $(CFLAGS) -c convert.c -o obj/convert.o

obj/main.o: main.c convert.h 
	$(CC) $(CFLAGS) -c main.c -o obj/main.o

clean:
	rm obj/*
	rm -f convert
