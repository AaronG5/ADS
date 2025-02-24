// aaron.gandzumian@mif.stud.vu.lt
// Studento ID: 2413934
// Programa sukuria stack'o tipo duomenų struktūrą ir realizuoja stack'o manipuliacijos funkcijas
// (create, push, pop, peek, display, isEmpty, isFull)

#ifndef HEADER_H
#define HEADER_H
#include <stdbool.h>
#define MAX_SIZE 2

typedef struct Stack {
   int value;
   struct Stack *next;
}stack;
typedef struct StackProperties {
   stack *top;
   bool isCreated;
   int counter;
   bool isEmpty;
} stackProperties;

//Creation of stack
stackProperties *createStack(stackProperties *stack);

//Pushes value into stack's top
void push(int value, stackProperties **top);

//removes top value from stack
int pop(stackProperties **stackP);

//prints stack's top value
void peek(stackProperties *stackP);

//prints the whole stack
void displayStack(stackProperties *stackP);

//checks if stack is empty
bool isStackEmpty(stackProperties *stackP);

//checks if stack is full
bool isStackFull(stackProperties *stackP);

//stack deletion
void deleteStack(stackProperties **stackP);

#endif