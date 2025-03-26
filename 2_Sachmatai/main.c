#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

long long step = 0;
long long amount = 0;

int main() {
   
   unsigned col = 0, row = 0, answer[2][N][N], matrix[N][N] = {FREE_SQUARE};
   
   char buffer[350];
   char *trumpas = "out-trumpas.txt";
   char *ilgas = "out-ilgas.txt";
   
   FILE *shortFile = fopen(trumpas, "w");
   FILE *longFile = fopen(ilgas, "w");

   sprintf(buffer, "2-oji Uzduotis. 7 variantas. Aaron Gandzumian, PS 2 grupe 1 pogrupis. Data: 2025-03-21\n\n"
      "Salyga: sustatyti N dydzio sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis.\n"
      "APRIBOJIMAI. Sachmatu lenta turetu buti 7x7, 8x8 arba 9x9 dydzio.\n\n"
      "SPRENDIMO IDEJA. Perrenkami visi galimi 4 juodu rikiu variantai, nuosekliai, per\n");
   print(buffer, shortFile, longFile);

   sprintf(buffer, "eilute, pradedant nuo 1 iki 8, o eiluteje per stulpelius, pradedant nuo A iki H, iki\n"
      "kol yra kertami visi juodi langeliai. Po to yra perrenkami 4 balti rikiai, tokiu pat \n" 
      "principu kaip ir juodieji.\n"
      "Netinka - rikiai nekerta visu juodu/baltu langeliu, BACKTRACK - griztama prie praeito rikio.\n"
      "J - juodasis rikis.   B - baltasis rikis.\n");
   print(buffer, shortFile, longFile);

   printBoard(matrix, shortFile, longFile);

   sprintf(buffer, "\nPIRMA DALIS. Informacija ir pradiniai duomenys\n   "
      "1. SALYGA. Sustatyti N x N (kai N = 7, 8, 9) sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis, rasti imanomus sprendimus.\n   "
      "2. Lenta: %dx%d.\n   3. Rikiu skaicius: %d.\n", N, N, BISHOP_AMOUNT);
   print(buffer, shortFile, longFile);

   sprintf(buffer, "\nANTRA DALIS. Vykdymas.   (X, Y) - X atitinka stulpelius, Y atitinka eilutes");
   printf("%s", buffer);
   fprintf(longFile, "%s", buffer);

   solve(col, row, matrix, answer, 1, true, longFile);
   
   char resultMsg[200];
   if(amount) {
      sprintf(resultMsg, "1) Uzkloti lenta imanoma: %lld skirtingais budais.\n", amount);
   }
   else {
      sprintf(resultMsg, "Nepavyko uzkloti lentos.\n");
   }

   sprintf(buffer, "\n\nTRECIA DALIS. Rezultatai.\n   %s   2) Zingsniu prireike: %lld.\n", resultMsg, step);
   print(buffer, shortFile, longFile);

   if(amount) {
      printBoard(answer[0], shortFile, longFile);
      printBoard(answer[1], shortFile, longFile);
   }

   fclose(shortFile);
   fclose(longFile);
}