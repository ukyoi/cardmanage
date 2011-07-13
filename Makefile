main: main.o func.o
	gcc -g main.o func.o -o main

main.o: main.c func.h func.c
	gcc -c main.c

func.o: func.h func.c
	gcc -c func.c

clean:
	@echo "Cleanning."
	rm main.o func.o
