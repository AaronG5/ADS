#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

stackProperties *createStack(stackProperties *stack) // Creates new stack with a value placed inside
{
   stackProperties *newStack = (stackProperties*)malloc(sizeof(stackProperties));
   if (newStack == NULL)
   {
      printf("Error allocating memory for stack.\n");
      return NULL;
   }
   else if(stackP->isCreated = true) {
      printf("Stack is already created\n");
   }
   else
   {
      newStack->top = NULL;
      newStack->isCreated = true;
      newStack->counter = 0;
      newStack->isEmpty = true;
      return newStack;
   }
}

void push(int value, stackProperties **stackP) // Pushes element onto top of stack
{
   if (*stackP == NULL || !((*stackP)->isCreated)) {
      printf("Stack is not created.\n");
   }

   stack *newElement = (stack *)malloc(sizeof(stack));
   if (newElement == NULL || (*stackP)->counter >= MAX_SIZE)
   {
      printf("Maximum stack size reached! (expected overflow)\n");
   }
   else
   {
      if((*stackP)->isEmpty) {
         (*stackP)->isEmpty = false;
      }
      newElement->value = value;
      newElement->next = (*stackP)->top;
      (*stackP)->top = newElement;
      (*stackP)-> counter ++;
   }
}

int pop(stackProperties **stackP) // Pops top element out of stack
{
   if (*stackP == NULL || (*stackP)->isEmpty)
   {
      printf("Stack is empty (expected underflow).\n");
      return -1;
   }
   else
   {
      if(!(*stackP)->isEmpty && (*stackP)->top->next == NULL) {
         (*stackP)->isEmpty = true;
      }
      int topValue = (*stackP)->top->value;
      stack *temp; //= (stackProperties*)malloc(sizeof(stackProperties));
      // if (temp == NULL) {
      //    printf("Error allocating memory for stack.\n");
      //    return -1;
      // }
      temp = (*stackP)->top;
      //free(stackP->top)
      (*stackP)->top = (*stackP)->top->next;
      free(temp);
      (*stackP)->counter--;
      return topValue;
   }
}

void peek(stackProperties *stackP) // Prints the top element of stack
{
   if (stackP == NULL || stackP->isEmpty)
   {
      printf("Stack is empty, nothing to print.\n");
   }
   else
   {
      printf("%d\n", stackP->top->value);
   }
}

void displayStack(stackProperties *stackP) // Displays entire contents of stack from top to bottom
{
   if (stackP == NULL || stackP->isEmpty)
   {
      printf("Stack is empty, nothing to display.\n");
   }
   else
   {
      printf(" --Top of stack--\n");
      stack *temp = stackP->top;
      for(int i = 0; i < stackP->counter; i++) {
         printf("%d\n", stackP->top->value);
         stackP -> top = stackP->top->next;
      }
      printf("--Bottom of stack--\n");
      stackP->top = temp;
   }
}

bool isStackEmpty(stackProperties *stackP) // Checks if stack is full (True/False)
{
   return stackP->isEmpty ? true : false;
   
}

bool isStackFull(stackProperties *stackP) // Checks if stack is full (True/False)
{
   return (stackP->counter == MAX_SIZE) ? true : false;
   
}

void deleteStack(stackProperties **stackP) {
   for(int i = 0; i < (*stackP)->counter; i++) {
      stack *temp = (*stackP)->top;
      (*stackP) -> top = (*stackP)->top->next;
      free(temp);
   }
   (*stackP) -> isCreated = false;
}
