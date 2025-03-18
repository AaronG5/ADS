#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// TODO: make it print to file
// TODO: make it check for limit of rook pieces (8)

#define SIZE 7
#define ROOK_AMOUNT 8

int step = 0;
int amount = 0;

void stepInfo(char *buffer, int row, int col, bool deeper, bool isBackTrack) {
   char depth[SIZE] = "\0";
   //int len = 0;

   for(int i = 0; i < row - 1; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "%6d)  %sR%d. Col=%c. Row=%d. %s %s", ++step, depth, col, col + 64, row, (deeper ? "Tinka." : "Netinka."), (isBackTrack ? "Backtrack." : ""));

   printf("\n%s", buffer);
}

void recursion(int n, int row, bool usedCol[], int combination[], char *buffer) {
   bool deeper;
   int oldAmount = amount;


   if(row == n) {
      printf("End reached! ");
      for(int i = 0; i < row; ++i) {
         printf("%c ", combination[i] + 65);
      }
      ++amount;
      return;
   }

   for(int i = 0; i < n; ++i) {
      deeper = true;

      
      if(usedCol[i]) {
         deeper = false;
      }

      stepInfo(buffer, row + 1, i + 1, deeper, false);
      
      if(deeper) {
         usedCol[i] = true;
         combination[row] = i;
         recursion(n, row+1, usedCol, combination, buffer);
         usedCol[i] = false;
      }
   }
   if(oldAmount < amount) {
      printf("Backtrack. ");
   }
}

int main() {
   int n = SIZE, row = 0, combination[SIZE];
   bool usedCol[SIZE] = {false};
   char buffer[100];

   printf("PIRMA DALIS. Duomenys\n   1) Lenta: %dx%d.\n   2) Rikiu skaicius: %d.\n", SIZE, SIZE, ROOK_AMOUNT);

   printf("\nANTRA DALIS. Vykdymas");
   recursion(n, row, usedCol, combination, buffer);

   printf("\n\nTRECIA DALIS. Rezultatai\n   1) Uzkloti lenta imanoma: %d skirtingais budais.\n   2) Zingsniu prireike: %d.\n", amount, step);
}