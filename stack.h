// aaron.gandzumian@mif.stud.vu.lt
// Studento ID: 2413934
// Programa sukuria stack'o tipo duomenų struktūrų masyvą ir realizuoja stack'o manipuliacijos funkcijas
// (createStack, push, pop, peek, displayStack, isStackEmpty, isStackFul, deleteStack)

#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_SIZE 2
#define MAX_STACK_AMOUNT 3
#define USING_MENU 1
#define NOT_USING_MENU 0


typedef struct Stack {
   int value;
   struct Stack *next;
} stack;

typedef struct StackProperties {
   stack *top;
   char stackName;
   bool isCreated;
   bool isEmpty;
   int counter;
} stackProperties;


int validateUserInput(int intUsedForMenu);

int chooseStackABC(stackProperties *stackP[], bool creationMode);

// Creation of stack
stackProperties *createStack(stackProperties **stack, int *stackNum, int stackVar);

// Push value onto top of stack
void push(stackProperties **top, int value);

// Remove top value from stack
int pop(stackProperties **stackP);

// Print stack top value
void peek(stackProperties *stackP);

// Print the whole stack
void displayStack(stackProperties *stackP);

// Check if stack is empty
bool isStackEmpty(stackProperties *stackP);

// Check if stack is full
bool isStackFull(stackProperties *stackP);

// Delete stack
void deleteStack(stackProperties **stackP);

#endif