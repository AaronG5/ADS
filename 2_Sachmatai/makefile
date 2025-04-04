program: main.o bishop.o
	gcc bishop.o main.o -o program

main.o: main.c bishop.h
	gcc -c -Wall main.c -o main.o

stack.o: bishop.c bishop.h
	gcc -c -Wall bishop.c -o bishop.o

run: program
	./program

clean:
	rm *.o program *.txt
	clear