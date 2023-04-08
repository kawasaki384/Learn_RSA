all: main.c
	gcc main.c -o main -lm
run: all
	./main
