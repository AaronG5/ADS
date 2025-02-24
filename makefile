program: main.o stack.o
	gcc stack.o main.o -o program

main.o: main.c stack.h
	gcc -c main.c -o main.o

stack.o: stack.c stack.h
	gcc -c stack.c -o stack.o

test.o: test.c stack.h
	gcc -c test.c -o test.o

run: program
	./program

clean:
	rm *.o program

test: test.o stack.o
	gcc test.o stack.o -o program