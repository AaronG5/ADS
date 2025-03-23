#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

long long step = 0;
long long amount = 0;

int main() {
   
   int col = 0, row = 0, combination[N], matrix[N][N] = {FREE_SQUARE};
   
   char buffer[350];
   char *trumpas = "out-trumpas.txt";
   char *ilgas = "out-ilgas.txt";
   
   FILE *shortFile = fopen(trumpas, "w");
   FILE *longFile = fopen(ilgas, "w");

   sprintf(buffer, "2-oji Uzduotis. 7 variantas. Aaron Gandzumian, PS 2 grupe 1 pogrupis. Data: 2025-03-21\n"
      "PIRMA DALIS. Informacija ir pradiniai duomenys\n   "
      "1. SALYGA. Sustatyti N x N (kai N = 7, 8, 9) sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis, rasti imanomus sprendimus.\n   "
      "2. Lenta: %dx%d.\n   3. Rikiu skaicius: %d.\n", N, N, BISHOP_AMOUNT);
   printf("%s", buffer);
   fprintf(shortFile, "%s", buffer);
   fprintf(longFile, "%s", buffer);

   sprintf(buffer, "\nANTRA DALIS. Vykdymas");
   printf("%s", buffer);
   fprintf(longFile, "%s", buffer);

   recursion(col, row, matrix, 0, true, longFile);
   
   sprintf(buffer, "\n\nTRECIA DALIS. Rezultatai\n   1) Uzkloti lenta imanoma: %lld skirtingais budais.\n   2) Zingsniu prireike: %lld.\n", amount, step);
   printf("%s", buffer);
   fprintf(shortFile, "%s", buffer);
   fprintf(longFile, "%s", buffer);

   printf("  ");
   for(int j = 0; j < N; ++j) {
      printf("  %c ", j + 65);
   }
   for(int i = N-1; i >= 0; --i) {
      printf("\n  +");
      for(int j = 0; j < N; ++j) {
         printf("---+");
      }
      printf("\n%d |", i+1);
      for(int j = 0; j < N; ++j) {
         printf(" %d |", matrix[i][j]);
      }
   }
   printf("\n  +");
   for(int j = 0; j < N; ++j) {
      printf("---+");
   }

   fclose(shortFile);
   fclose(longFile);
}