#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int validateUserInput(int intUsedForMenu) {
   int userInt;
   char newLine;

   while(1) {
      if(!intUsedForMenu) {
         printf("Įveskite reikšmę, skirtą patalpinti į steką.\n");
      }
      if(scanf(" %d%c", &userInt, &newLine) && newLine == '\n') {
         if(intUsedForMenu && userInt < 11 && userInt > 0) {
            return userInt;
         }
         else if(intUsedForMenu) {
            printf("Įvyko klaida (%d), neteisinga reikšmė.\n", ERR_INVALID_INPUT);
            continue;
         }
         return userInt;
      }
      else {
         printf("Įvyko klaida (%d), netaisyklinga įvestis.\n", ERR_INVALID_INPUT);
         while(getchar() != '\n');
      }
   }
}

int chooseStackABC(stackProperties *stackP[], bool creationMode) {
   int stackVariant;
   char stackLetter, newLine;

   if(!creationMode) {
      bool foundCreatedStacks = false;
      for(int i = 0; i < MAX_STACK_AMOUNT; ++i) {
         if(stackP[i] != NULL && stackP[i]->isCreated) {
            foundCreatedStacks = true;
         }
      }
      if(!foundCreatedStacks) {
         printf("Įvyko klaida (%d), nėra sukurtų stekų.\n", ERR_SEGMENTATION_FAULT);
         return -1;
      }
   }

   printf("Pasirinkite steką iš apatinio sarašo:\n");
   
   if(creationMode) {
      printf("[A], [B], [C]\n");
   }
   
   else {
      for(int i = 0; i < MAX_STACK_AMOUNT; ++i) {
         if(stackP[i] != NULL && stackP[i]->isCreated) {
            printf("[%c] ", stackP[i]->stackName);
         }
      }
      printf("\n");
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
               printf("Įvyko klaida (%d), netaisyklingas steko pavadinimas, bandykite dar kartą.\n", ERR_INVALID_INPUT);
               continue;
         }

         if(stackVariant >= 0 && !creationMode && (stackP[stackVariant] == NULL)) {
             printf("Įvyko klaida (%d), pasirinktas stekas dar nėra sukurtas, pasirinkite kitą.\n", ERR_SEGMENTATION_FAULT);
             continue; 
         }
         return stackVariant;
      }
      else {
         printf("Įvyko klaida (%d), netaisyklingas įvedimas, bandykite dar kartą.\n", ERR_INVALID_INPUT);
         while (getchar() != '\n');
      }
   }
}


stackProperties *createStack(stackProperties **stackP, int *stackNum, int stackVar)
{
   if(*stackNum == MAX_STACK_AMOUNT) {
      printf("Įvyko klaida (%d), maksimalus stekų kiekis pasiektas (%d).\n", ERR_STACK_OVERFLOW , MAX_STACK_AMOUNT);
      return NULL;
   }

   stackProperties *newStack = (stackProperties*)malloc(sizeof(stackProperties));
   if (newStack == NULL) {
      printf("Įvyko klaida (%d), nepavyko priskirti atminties stekui.\n", ERR_OUT_OF_MEMORY);
      return NULL;
   }
   else if((*stackP) != NULL && (*stackP)->isCreated == true) {
      printf("Įvyko klaida (%d), stekas jau buvo sukurtas.\n", ERR_DUPLICATE_DEC);
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

      printf("Stekas %c sėkmingai sukurtas.\n", stackVar);
      return newStack;
   }
}

void push(stackProperties **stackP, int value) // Pushes element onto top of stack
{
   if (*stackP == NULL || !((*stackP)->isCreated)) {
      printf("Įvyko klaida (%d), stekas nėra sukurtas.\n", ERR_SEGMENTATION_FAULT);
      return;
   }

   stack *newElement = (stack *)malloc(sizeof(stack));
   if (newElement == NULL || (*stackP)->counter >= MAX_SIZE) {
      printf("Įvyko klaida (%d), maksimalus steko elementų kiekis pasiektas (%d).\n", ERR_STACK_OVERFLOW, MAX_SIZE);
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
      printf("Skaičius %d sėkmingai įdėtas į steką %c.\n", value, (*stackP)->stackName);
   }
}

int pop(stackProperties **stackP) { // Pops top element out of stack
   if ((*stackP)->top == NULL) {
      printf("Įvyko klaida (%d), stekas tuščias.\n", ERR_STACK_UNDERFLOW);
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
      printf("Skaičius %d sėkmingai pašalintas iš steko %c.\n", topValue, (*stackP)->stackName);
      return topValue;
   }
}

void peek(stackProperties *stackP) { // Prints the top element of stack
   if (stackP == NULL || stackP->isEmpty) {
      printf("Įvyko klaida (%d), stekas tuščias, nėra ką spausdinti.\n", ERR_SEGMENTATION_FAULT);
   }
   else {
      printf("%d\n", stackP->top->value);
   }
}

void displayStack(stackProperties *stackP) { // Displays entire contents of stack from top to bottom
   if (stackP == NULL || stackP->isEmpty) {
      printf("Įvyko klaida (%d), stekas tuščias, nėra ką spausdinti.\n", ERR_SEGMENTATION_FAULT);
   }
   else {
      printf(" --Steko viršus--\n");
      stack *temp = stackP->top;
      for(int i = 0; i < stackP->counter; i++) {
         printf("%d\n", stackP->top->value);
         stackP -> top = stackP->top->next;
      }
      printf(" --Steko apačia--\n");
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
   (*stackP)->isCreated = false;
   
   printf("Stekas %c sėkmingai pašalintas.\n", (*stackP)->stackName);
}