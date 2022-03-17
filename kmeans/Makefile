CC = gcc -g
CFLAGS = -Iinclude
CLINK = -lm
OPT =

main.exe: main.o km.o
	$(CC) main.o km.o -fopenmp -o main.exe $(CLINK)

main.o: main.c
	$(CC) $(CFLAGS) $(OPT) -fopenmp -c main.c -o main.o

km.o: src/km.c
	$(CC) $(OPT) -fopenmp -c src/km.c -o km.o

clean:
	rm *.o *.exe
