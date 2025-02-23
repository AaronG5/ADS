#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack *createStack(int value) // Creates new stack with a value placed inside
{
   stack *newStack = (stack *)malloc(sizeof(stack));
   if (newStack == NULL)
   {
      printf("Error allocating memory for stack.\n");
      return NULL;
   }
   else
   {
      newStack->value = value;
      newStack->next = NULL;
      return newStack;
   }
}

void push(int value, stack **top) // Pushes element onto top of stack
{
   stack *newElement = (stack *)malloc(sizeof(stack));
   if (newElement == NULL)
   {
      printf("Maximum stack size reached! (expected overflow)\n");
   }
   else
   {
      newElement->value = value;
      newElement->next = *top;
      *top = newElement;
   }
}

void pop(stack **top) // Pops top element out of stack
{
   if (*top == NULL)
   {
      printf("Stack is empty (expected underflow).\n");
   }
   else
   {
      stack *temp = *top;
      *top = (*top)->next;
      free(temp);
   }
}

void peek(stack *top) // Prints the top element of stack
{
   if (top == NULL)
   {
      printf("Stack is empty, nothing to print.\n");
   }
   else
   {
      printf("%d\n", top->value);
   }
}

void displayStack(stack *top) // Displays entire contents of stack from top to bottom
{
   if (top == NULL)
   {
      printf("Stack is empty, nothing to display.\n");
   }
   else
   {
      printf(" --Top of stack--");
      do
      {
         printf("%d\n", top->value);
         top = top->next;
      } while (top != NULL);
      printf("--Bottom of stack--");
   }
}

int isEmpty(stack *top) // Checks if stack is full (True/False)
{
   if (top == NULL)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

int isFull(stack *top) // Checks if stack is full (True/False)
{
   stack *newElement = (stack *)malloc(sizeof(stack));
   if (newElement == NULL)
   {
      free(newElement);
      return 1;
   }
   else
   {
      free(newElement);
      return 0;
   }
}
