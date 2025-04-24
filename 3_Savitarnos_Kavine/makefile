CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -c -Wno-self-assign-overloaded -Wno-unused-variable

PROGRAM = program

run: make
	./$(PROGRAM)

make: main.o cafe.o
	$(CC) cafe.o main.o -o $(PROGRAM)

main.o: main.cpp cafe.h
	$(CC) $(CFLAGS) main.cpp -o main.o

cafe.o: cafe.cpp cafe.h
	$(CC) $(CFLAGS) cafe.cpp -o cafe.o

clean:
	rm *.o $(PROGRAM)

rebuild:
	$(MAKE) clean
	$(MAKE) make