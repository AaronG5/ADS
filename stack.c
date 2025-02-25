#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int validateUserInput(int intUsedForMenu) {
   int userInt;
   char newLine;

   while(1) {
      if(scanf(" %d%c", &userInt, &newLine) && newLine == '\n') {
         if(intUsedForMenu && userInt < 9 && userInt >= 0) {
            return userInt;
         }
         else if(intUsedForMenu) {
            printf("Error, incorrect value.\n");
            continue;
         }
         return userInt;
      }
      else {
         printf("Error, incorrect value.\n");
         while(getchar() != '\n');
      }
   }
}

int chooseStackABC(stackProperties *stackP[], bool creationMode) {
   int stackVariant;
   char stackLetter, newLine;

   printf("Please choose from the list below\n");
   
   if(creationMode) {
      printf("[A], [B], [C]\n");
   }
   
   else {
      bool foundCreatedStacks = false;
      for(int i = 0; i < MAX_STACK_AMOUNT; ++i) {
         if(stackP[i] != NULL && stackP[i]->isCreated) {
            printf("[%c] ", stackP[i]->stackName);
            foundCreatedStacks = true;
         }
      }
      printf("\n");

      if(!foundCreatedStacks) {
         printf("No available stacks.\n");
         return -1;
      }
   }

   while(1) {
      if(scanf(" %c", &stackLetter)) {
         switch(stackLetter) {
            case 'A':
            case 'a':
               stackVariant = 0;
               break;

            case 'B':
            case 'b':
               stackVariant = 1;
               break;

            case 'C':
            case 'c': 
               stackVariant = 2;
               break;

            default:
               printf("Invalid stack variant, please try again.\n");
               continue;
         }

         if(stackVariant >= 0 && !creationMode && (stackP[stackVariant] == NULL)) {
             printf("The selected stack has not been created. Please choose another.\n");
             continue; 
         }
         return stackVariant;
      }
      else {
         printf("Invalid input. Please try again.\n");
         while (getchar() != '\n');
      }
   }
}


stackProperties *createStack(stackProperties **stackP, int *stackNum, int stackVar)
{
   if(*stackNum == MAX_STACK_AMOUNT) {
      printf("Maximum stack amount reached! (%d)\n", MAX_STACK_AMOUNT);
      return NULL;
   }

   stackProperties *newStack = (stackProperties*)malloc(sizeof(stackProperties));
   if (newStack == NULL) {
      printf("Error allocating memory for stack.\n");
      return NULL;
   }
   else if((*stackP) != NULL && (*stackP)->isCreated == true) {
      printf("Stack is already created\n");
      return *stackP;
   }
   else {
      newStack->top = NULL;
      newStack->isCreated = true;
      newStack->isEmpty = true;
      newStack->counter = 0;
      (*stackNum)++;

      switch(stackVar) {
         case 0: 
            newStack->stackName = 'A';
            break;

         case 1:
            newStack->stackName = 'B';
            break;

         case 2:
            newStack->stackName = 'C';
            break;
      }

      printf("Stack %c successfully created.\n", stackVar);
      return newStack;
   }
}

void push(stackProperties **stackP, int value) // Pushes element onto top of stack
{
   if (*stackP == NULL || !((*stackP)->isCreated)) {
      printf("Stack is not created.\n");
      return;
   }

   stack *newElement = (stack *)malloc(sizeof(stack));
   if (newElement == NULL || (*stackP)->counter >= MAX_SIZE) {
      printf("Maximum stack size reached! (%d)\n", MAX_SIZE);
      return;
   }
   else {
      if((*stackP)->isEmpty) {
         (*stackP)->isEmpty = false;
      }
      newElement->value = value;
      newElement->next = (*stackP)->top;
      (*stackP)->top = newElement;
      (*stackP)-> counter ++;
      printf("Succesfully pushed %d to stack.\n", value);
   }
}

int pop(stackProperties **stackP) { // Pops top element out of stack
   if (*stackP == NULL || (*stackP)->isEmpty) {
      printf("Stack is empty.\n");
      return -1;
   }
   else {
      if(!(*stackP)->isEmpty && (*stackP)->top->next == NULL) {
         (*stackP)->isEmpty = true;
      }
      int topValue = (*stackP)->top->value;
      stack *temp; 

      temp = (*stackP)->top;
      (*stackP)->top = (*stackP)->top->next;
      free(temp);
      (*stackP)->counter--;
      printf("Succesfully popped %d from stack.\n", topValue);
      return topValue;
   }
}

void peek(stackProperties *stackP) { // Prints the top element of stack
   if (stackP == NULL || stackP->isEmpty) {
      printf("Stack is empty, nothing to print.\n");
   }
   else {
      printf("%d\n", stackP->top->value);
   }
}

void displayStack(stackProperties *stackP) { // Displays entire contents of stack from top to bottom
   if (stackP == NULL || stackP->isEmpty) {
      printf("Stack is empty, nothing to display.\n");
   }
   else {
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

bool isStackEmpty(stackProperties *stackP) { // Checks if stack is full (True/False)
   return stackP->isEmpty ? true : false;
   
}

bool isStackFull(stackProperties *stackP) { // Checks if stack is full (True/False)
   return (stackP->counter == MAX_SIZE) ? true : false;
   
}

void deleteStack(stackProperties **stackP) {
   for(int i = 0; i < (*stackP)->counter; i++) {
      stack *temp = (*stackP)->top;
      (*stackP) -> top = (*stackP)->top->next;
      free(temp);
   }
   (*stackP) -> isCreated = false;
   
   printf("Stack %c deleted successfully.\n", (*stackP)->stackName);
}
