#include <stdio.h>
#include "stack.h"

int main() 
{
   int userInput;
   stackProperties *stacksABC[MAX_STACK_AMOUNT];
   int stackNum = 0;

   for(int i = 0; i < MAX_STACK_AMOUNT; ++i) {
      stacksABC[i] = NULL;
   }

   char *menu = "\n 1. Sukurti tuščią steką\n"
      " 2. Įdėti reikšmę į steką (push)\n"
      " 3. Išimti reikšmę iš steko (pop)\n"
      " 4. Patikrinti viršutinę steko reikšmę\n"
      " 5. Išspausdinti visas steko reikšmes\n"
      " 6. Patikrinti, ar stekas tuščias\n"
      " 7. Patikrinti, ar stekas pilnas\n"
      " 8. Pašalinti steką\n"
      " 9. Atspausdinti meniu į ekraną\n"
      "10. Baigti programą\n\n";

   printf("\033[H\033[J");
   printf("%s", menu);

   while(1) {
      userInput = validateUserInput(USING_MENU);
      int tempABC, chosenStack;

      if(userInput != 10 && userInput != 1 && userInput != 9) {
         chosenStack = chooseStackABC(stacksABC, false);
         if(chosenStack < 0) {
            continue;
         }
      }

      switch(userInput) {
         case 1:
            tempABC = chooseStackABC(stacksABC, true);
            stacksABC[tempABC] = createStack((&stacksABC[tempABC]), &stackNum, tempABC);
            break;

         case 2:
            push(&stacksABC[chosenStack], validateUserInput(NOT_USING_MENU));
            break;

         case 3:
            pop(&stacksABC[chosenStack]);
            break;

         case 4:
            peek(stacksABC[chosenStack]);
            break;

         case 5:
            displayStack(stacksABC[chosenStack]);
            break;

         case 6:
            printf("%s", isStackEmpty(stacksABC[chosenStack]) ? "Stekas tuščias.\n" : "Stekas nėra tuščias.\n");
            break;

         case 7:
            printf("%s", isStackFull(stacksABC[chosenStack]) ? "Stekas pilnas.\n" : "Stekas nėra pilnas.\n");
            break;

         case 8:
            deleteStack(&stacksABC[chosenStack]);
            break;
         
         case 9:
            printf("\033[H\033[J");
            printf("%s", menu);
            break;
         
         case 10:
            return 0;
      }
   }
   return 0;
}