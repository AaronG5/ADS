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
   
      sprintf(buffer, "2 Uzd. 7 var. Aaron Gandzumian, PS 2 gr. 1 pogr. Data: 25-03-2025\n\n"
         "SALYGA.\nSustatyti N*N sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis.\nIstirti 3 testais: N=8, 7, 9.\n\n"
         "SPRENDIMO IDEJA. Perrenkami visi galimi 4 juodu rikiu variantai, nuosekliai, per\n");
      print(buffer, outputFile);
   
      sprintf(buffer, "eilute, pradedant nuo 1 iki 8, o eiluteje per stulpelius, pradedant nuo A iki H, iki\n"
         "kol yra kertami visi juodi langeliai. Po to yra perrenkami 4 balti rikiai, tokiu pat \n" 
         "principu kaip ir juodieji.\n\n"
         "Netinka - rikiai nekerta visu juodu/baltu langeliu, BACKTRACK, nesekme - griztama prie praeito rikio.\n"
         "J - juodasis rikis.   B - baltasis rikis.\n");
      print(buffer, outputFile);
   
      printBoard(matrix, outputFile, -1);
   
      sprintf(buffer, "\nPIRMA DALIS. Informacija ir pradiniai duomenys\n   "
         "1. SALYGA. Sustatyti N*N sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis.\n   "
         "2. Lenta: %dx%d.\n   3. Rikiu skaicius: %d.\n", N, N, BISHOP_AMOUNT);
      print(buffer, outputFile);
   
      sprintf(buffer, "\nANTRA DALIS. Vykdymas.   (X, Y) - X atitinka stulpelius, Y atitinka eilutes\n");
      print(buffer, outputFile);
   
      solve(col, row, matrix, answer, 1, true, outputFile);
      
      char resultMsg[200];
      if(amount) {
         sprintf(resultMsg, "1) Uzkloti lenta imanoma: %lld skirtingais budais.\n", amount);
      }
      else {
         sprintf(resultMsg, "Nepavyko uzkloti lentos.\n");
      }
   
      sprintf(buffer, "\n\nTRECIA DALIS. Rezultatai.\n   %s   2) Zingsniu prireike: %lld.\n", resultMsg, step);
      print(buffer, outputFile);
   
      if(amount) {
         for(int i = 0; i < AMOUNT_OF_ANSWERS; ++i) {
            printBoard(answer[i], outputFile, i+1);
         }
      }
   
      fclose(outputFile);
   }
}