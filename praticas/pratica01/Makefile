all: main.out matriz.o

matriz.o:
	gcc -c -lm -I include/ grafo_matriz.c -o obj/matriz.o

main.out:
	gcc -lm -I include/ -o run.out main.c obj/matriz.o