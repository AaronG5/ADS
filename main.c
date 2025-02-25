#include <stdio.h>

int main() 
{

   int userInput;

   printf(
      "=====================================================\n"
      "*  Spauskite 1 - sukurti steką                      *\n"
      "*  Spauskite 2 - įdėti reikšmę į steką (push)       *\n"
      "*  Spauskite 3 - išimti reikšmę iš steko (pop)      *\n"
      "*  Spauskite 4 - patikrinti viršutinę steko reikšmę *\n"
      "*  Spauskite 5 - atspausdinti visas steko reikšmes  *\n"
      "*  Spauskite 6 - patikrinti, ar stekas yra tuščias  *\n"
      "*  Spauskite 7 - patikrinti, ar stekas yra pilnas   *\n"
      "*  Spauskite 8 - ištrinti visus steko elementus     *\n"
      "*  Spauskite 0 - užbaigti programą                  *\n"
      "=====================================================\n\n"
  );

   while(1) {
      userInput = validUserInput();
      switch(userInput) {
         case 1:


         case 2:
      }
   }
// TODO: make menu interface for stack
// TODO: make multiple stacks work


   return 0;
}