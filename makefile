madharhaAnkushA1: madharhaAnkushA1.o main.o
	gcc -Wall -std=c99 madharhaAnkushA1.o main.o -o madharhaAnkushA1
madharhaAnkushA1.o: madharhaAnkushA1.c madharhaAnkushA1.h
	gcc -Wall -std=c99 -c madharhaAnkushA1.c
main.o: main.c madharhaAnkushA1.h
	gcc -Wall -std=c99 -c main.c
clean:
	rm *.o madharhaAnkushA1