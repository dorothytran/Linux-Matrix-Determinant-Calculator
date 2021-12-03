all: DET.o
	gcc -o all DET.o

DET.o: DET.c DET.h
	gcc -c DET.c