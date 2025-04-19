#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

int N = 6;
long long step;
long long amount;

int main() {
   
   for(int i = 0; i < 3; ++i) {
      ++N;
      step = 0;
      amount = 0;
      unsigned col = 0, row = 0, answer[AMOUNT_OF_ANSWERS][N][N], matrix[N][N];

      for(int j = 0; j < N; ++j) {
         for(int k = 0; k < N; ++k) {
            matrix[j][k] = FREE_SQUARE;
         }
      }

      char buffer[350];
      char fileName[50];
      sprintf(fileName, "2uzd-07var-protokolas%d-Gandzumian.txt", i + 1);
      
      FILE *outputFile = fopen(fileName, "w");
   
      sprintf(buffer, "2 uzduotis, 7 variantas. Aaron Gandzumian, PS 2 grupe 1 pogrupis.\n\n"
         "SALYGA.\nSustatyti N x N sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu\nbent vienas rikis.\n"
         "Rasti pirmus 10 sprendimu. Istirti 3 testais: N = 7, 8, 9.\n\n"
         "SPRENDIMO IDEJA.\nPerrenkami visi galimi 4 juodu rikiu variantai, nuosekliai, per\n");
      print(buffer, outputFile);
   
      sprintf(buffer, "eilute, pradedant nuo 1 iki 8, o eiluteje per stulpelius, pradedant\n"
         "nuo A iki H, iki kol yra kertami visi juodi langeliai. Po to yra\nperrenkami 4 balti rikiai, tokiu patmprincipu kaip ir juodieji.\n\n");
         print(buffer, outputFile);
      sprintf(buffer, "\"Netinka\" reiskia, kad rikiai nekerta visu juodu/baltu langeliu.\nKai pasiekiamas lentos galas, naudojamas \"BACKTRACK, nesekme\", kurio \n"
         "metu griztama prie praeito rikio.\n"
         "J - juodasis rikis.   B - baltasis rikis.\n");
      print(buffer, outputFile);
   
      printBoard(matrix, outputFile, -1);
   
      sprintf(buffer, "\nPIRMA DALIS. Duomenys\n   "
         "1. N = %d. Lenta: %d x %d.\n   2. Rikiu skaicius: %d.\n", N, N, N, BISHOP_AMOUNT);
      print(buffer, outputFile);
   
      sprintf(buffer, "\nANTRA DALIS. Vykdymas.\n(X, Y) - X yra stulpeliai, Y yra eilutes.\n");
      print(buffer, outputFile);
   
      solve(col, row, matrix, answer, 1, true, outputFile);
      
      char resultMsg[200];
      if(amount) {
         sprintf(resultMsg, "Uzkloti lenta imanoma: %lld skirtingais budais.\n", amount);
      }
      else {
         sprintf(resultMsg, "Nepavyko uzkloti lentos.\n");
      }
   
      sprintf(buffer, "\n\nTRECIA DALIS. Rezultatai.\n   1) %s   2) Zingsniu skaicius: %lld.\n", resultMsg, step);
      print(buffer, outputFile);
   
      if(amount) {
         for(int i = 0; i < AMOUNT_OF_ANSWERS; ++i) {
            printBoard(answer[i], outputFile, i+1);
         }
      }
   
      fclose(outputFile);
   }
}