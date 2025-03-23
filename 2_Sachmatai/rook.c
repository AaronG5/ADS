#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// TODO: make it check for limit of rook pieces (8)

#define SIZE 4
#define ROOK_AMOUNT 8

int step = 0;
int amount = 0;

void stepInfo(char *buffer, int row, int col, bool deeper, bool isBackTrack, FILE *longFile) {
   char depth[SIZE] = "\0";
   //int len = 0;

   for(int i = 0; i < row - 1; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "\n%6d)  %sR%d. Col=%c. Row=%d. %s %s", ++step, depth, col, col + 64, row, (deeper ? "Gilyn." : "Klaida."), (isBackTrack ? "Backtrack." : ""));

   printf("%s", buffer);
   fprintf(longFile, "%s", buffer);
}

void recursion(int n, int row, bool usedCol[], int combination[], char *buffer, FILE *longFile) {
   bool deeper;
   int oldAmount = amount;


   if(row == n) {
      printf("End reached! ");
      fprintf(longFile, "End reached! ");
      for(int i = 0; i < row; ++i) {
         printf("%c ", combination[i] + 65);
         fprintf(longFile, "%c ", combination[i] + 65);
      }
      ++amount;
      return;
   }

   for(int i = 0; i < n; ++i) {
      deeper = true;

      
      if(usedCol[i]) {
         deeper = false;
      }

      stepInfo(buffer, row + 1, i + 1, deeper, false, longFile);
      
      if(deeper) {
         usedCol[i] = true;
         combination[row] = i;
         recursion(n, row+1, usedCol, combination, buffer, longFile);
         usedCol[i] = false;
      }
   }
   if(oldAmount < amount) {
      printf("Backtrack. ");
      fprintf(longFile, "Backtrack. ");
   }
}

int main() {
   
   int n = SIZE, row = 0, combination[SIZE];
   bool usedCol[SIZE] = {false};
   
   char buffer[120], protocolMsg[100];
   char *trumpas = "out-trumpas.txt";
   char *ilgas = "out-ilgas.txt";
   
   FILE *shortFile = fopen(trumpas, "w");
   FILE *longFile = fopen(ilgas, "w");

   sprintf(buffer, "2-oji Uzduotis. 7 variantas. Aaron Gandzumian, PS 2 grupe 1 pogrupis. Data: 2023-03-21\n"
      "PIRMA DALIS. Informacija ir pradiniai duomenys\n   "
      "1. SALYGA. Sustatyti N x N (kai N = 7, 8, 9) sachmatu lentoje 8 rikius, kad kiekviena langeli kirstu bent vienas rikis, rasti imanomus sprendimus."
      "Lenta: %dx%d.\n   2) Rikiu skaicius: %d.\n", SIZE, SIZE, ROOK_AMOUNT);
   printf("%s", buffer);
   fprintf(shortFile, "%s", buffer);
   fprintf(longFile, "%s", buffer);

   sprintf(buffer, "\nANTRA DALIS. Vykdymas");
   printf("%s", buffer);
   fprintf(longFile, "%s", buffer);

   recursion(n, row, usedCol, combination, buffer, longFile);

   sprintf(buffer, "\n\nTRECIA DALIS. Rezultatai\n   1) Uzkloti lenta imanoma: %d skirtingais budais.\n   2) Zingsniu prireike: %d.\n", amount, step);
   printf("%s", buffer);
   fprintf(shortFile, "%s", buffer);
   fprintf(longFile, "%s", buffer);

   fclose(shortFile);
   fclose(longFile);
}