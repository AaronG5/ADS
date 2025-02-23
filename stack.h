// aaron.gandzumian@mif.stud.vu.lt
// Studento ID: 2413934
// Programa sukuria stack'o tipo duomenų struktūrą ir realizuoja stack'o manipuliacijos funkcijas 
// (create, push, pop, peek, display, isEmpty, isFull)

#ifndef HEADER_H
#define HEADER_H

typedef struct Stack
{
    int value;
    struct Stack *next;
} stack;

stack *createStack(int value);

void push(int value, stack **top);

void pop(stack **top);

void peek(stack *top);

void displayStack(stack *top);

int isEmpty(stack *top);

int isFull(stack *top);

#endif