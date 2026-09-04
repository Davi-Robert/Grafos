all: main.out tempo.o

tempo.o:
	gcc -c -I include/ -o obj/tempo.o src/tempo.c

main.out:
	gcc -lm -l include/ -o bin/main.out src/main.c obj/tempo.o
