#include <stdio.h>
#include <stdbool.h>

#define SIZE 4
#define ROOK_AMOUNT 8

int step = 0;

void recursion(int n, int row, bool usedCol[], int combo[]) {
   bool deeper;
   
   if(row == n) {
      printf("End reached!\n");
      for(int i = 0; i < row; ++i) {
         printf("%d ", combo[i]);
      }
      printf("\n");
      return;
   }

   for(int i = 0; i < n; ++i) {
      deeper = true;

      if(usedCol[i]) {
         deeper = false;
      }

      if(deeper) {
         usedCol[i] = true;
         combo[row] = i;
         recursion(n, row+1, usedCol, combo);
         usedCol[i] = false;
      }
   }
}

int main() {
   int n = SIZE, row = 0, combo[SIZE];
   bool usedCol[SIZE] = {false};

   printf("PIRMA DALIS. Duomenys\n  1) Lenta: %dx%d. \n   2) Rikių skaičius: %d.\n", SIZE, SIZE, ROOK_AMOUNT);

   printf("ANTRA DALIS. Vykdymas\n");
   recursion(n, row, usedCol, combo);
   printf("Why are we here?\n");
}