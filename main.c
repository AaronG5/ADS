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

   char *menu = "=======================================================\n"
      "*  Spauskite [1] - sukurti steką                      *\n"
      "*  Spauskite [2] - įdėti reikšmę į steką (push)       *\n"
      "*  Spauskite [3] - išimti reikšmę iš steko (pop)      *\n"
      "*  Spauskite [4] - patikrinti viršutinę steko reikšmę *\n"
      "*  Spauskite [5] - išspausdinti visas steko reikšmes  *\n"
      "*  Spauskite [6] - patikrinti, ar stekas yra tuščias  *\n"
      "*  Spauskite [7] - patikrinti, ar stekas yra pilnas   *\n"
      "*  Spauskite [8] - ištrinti visus steko elementus     *\n"
      "*  Spauskite [9] - atspausdinti meniu į ekraną        *\n"
      "*  Spauskite [0] - užbaigti programą                  *\n"
      "=======================================================\n\n";

   printf("%s", menu);

   while(1) {
      userInput = validateUserInput(USING_MENU);
      int tempABC, chosenStack;

      if(userInput != 0 && userInput != 1 && userInput != 9) {
         chosenStack = chooseStackABC(stacksABC, false);
         if(chosenStack < 0) {
            continue;
         }
      }

      switch(userInput) {
         case 0:
            return 0;

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
      }
   }
   return 0;
}