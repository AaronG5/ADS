// aaron.gandzumian@mif.stud.vu.lt
// Studento ID: 2413934
// Programa sukuria stack'o tipo duomenų struktūrų masyvą ir realizuoja stack'o manipuliacijos funkcijas
// (createStack, push, pop, peek, displayStack, isStackEmpty, isStackFul, deleteStack)

#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define MAX_SIZE               2
#define MAX_STACK_AMOUNT       3
#define USING_MENU             1
#define NOT_USING_MENU         0

//Error define
#define ERR_STACK_OVERFLOW     1
#define ERR_STACK_UNDERFLOW    2
#define ERR_OUT_OF_MEMORY      3
#define ERR_SEGMENTATION_FAULT 4
#define ERR_DUPLICATE_DEC      5
#define ERR_INVALID_INPUT      6


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

// Įvesto skaičiaus validacija
int validateUserInput(int intUsedForMenu);

// Steko pasirinkimas tarp A, B ir C
int chooseStackABC(stackProperties *stackP[], bool creationMode);

// Steko sukūrimas (A, B ar C)
stackProperties *createStack(stackProperties **stack, int *stackNum, int stackVar);

// Elemento įdėjimas į steko viršūnę
void push(stackProperties **top, int value);

// Elemento išėmimas iš steko viršūnės
int pop(stackProperties **stackP);

// Steko viršūnės atspausdinimas į ekraną
void peek(stackProperties *stackP);

// Steko turinio atspausdinimas į ekraną
void displayStack(stackProperties *stackP);

// Tikrinama ar stekas tuščias
bool isStackEmpty(stackProperties *stackP);

// Tikrinama ar stekas pilnas
bool isStackFull(stackProperties *stackP);

// Steko ištrynimas
void deleteStack(stackProperties **stackP);

#endif