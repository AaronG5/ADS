#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

// TODO: figure out why double backtrack
int N = 6;
long long step;
long long amount;

int main() {
   
   for(int i = 0; i < 3; ++i) {
      ++N;
      step = 0;
      amount = 0;
      unsigned col = 0, row = 0, answer[2][N][N], matrix[N][N];

      for(int j = 0; j < N; ++j) {
         for(int k = 0; k < N; ++k) {
            matrix[j][k] = FREE_SQUARE;
         }
      }

      char buffer[350];
      char fileName[50];
      sprintf(fileName, "2uzd-07var-protokolas%d-Gandzumian.txt", i + 1);
      
      FILE *outputFile = fopen(fileName, "w");
   
      sprintf(buffer, "2-oji Uzduotis. 7 variantas. Aaron Gandzumian, PS 2 grupe 1 pogrupis. Data: 25-03-2025\n\n"
         "Salyga: sustatyti N dydzio sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis.\n"
         "APRIBOJIMAI. Sachmatu lenta turetu buti 7x7, 8x8 arba 9x9 dydzio.\n\n"
         "SPRENDIMO IDEJA. Perrenkami visi galimi 4 juodu rikiu variantai, nuosekliai, per\n");
      print(buffer, outputFile);
   
      sprintf(buffer, "eilute, pradedant nuo 1 iki 8, o eiluteje per stulpelius, pradedant nuo A iki H, iki\n"
         "kol yra kertami visi juodi langeliai. Po to yra perrenkami 4 balti rikiai, tokiu pat \n" 
         "principu kaip ir juodieji.\n"
         "Netinka - rikiai nekerta visu juodu/baltu langeliu, BACKTRACK - griztama prie praeito rikio.\n"
         "J - juodasis rikis.   B - baltasis rikis.\n");
      print(buffer, outputFile);
   
      printBoard(matrix, outputFile);
   
      sprintf(buffer, "\nPIRMA DALIS. Informacija ir pradiniai duomenys\n   "
         "1. SALYGA. Sustatyti N x N (kai N = 7, 8, 9) sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis, rasti imanomus sprendimus.\n   "
         "2. Lenta: %dx%d.\n   3. Rikiu skaicius: %d.\n", N, N, BISHOP_AMOUNT);
      print(buffer, outputFile);
   
      sprintf(buffer, "\nANTRA DALIS. Vykdymas.   (X, Y) - X atitinka stulpelius, Y atitinka eilutes");
      printf("%s", buffer);
      fprintf(outputFile, "%s", buffer);
   
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
         printBoard(answer[0], outputFile);
         printBoard(answer[1], outputFile);
      }
   
      fclose(outputFile);
   }
}