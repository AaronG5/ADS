CC = gcc
CFLAGS = -Wall
FILES = main.o stack.o 
OUT_EXE = stack.exe

build: $(FILES)
	$(CC) $(FILES) -o $(OUT_EXE)

main.o: main.c stack.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f *.o *.exe

rebuild:
	$(MAKE) clean
	$(MAKE) build