#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

// TODO: make it check for limit of bishop pieces (8)

bool isBoardDominated(int matrix[N][N], bool isWhite) {
   for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
         if(isWhite && (i + j) % 2 == 0 && matrix[i][j] == FREE_SQUARE) {
            return false;
         }
         if(!isWhite && (i + j) % 2 == 1 && matrix[i][j] == FREE_SQUARE) {
            return false;
         }
      }
   }
   return true;
}

bool isValidPlacement(int row, int col, int matrix[N][N]) {
   if(matrix[row][col] == FREE_SQUARE) {
      printf("Col = %d, Row = %d\n", col, row);
      return true;
   }
   return false;
}

void placeBishop(int row, int col, int matrix[N][N]) {
   matrix[row][col] = STANDING; // Place bishop

   for(int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
      if(matrix[i][j] == FREE_SQUARE) matrix[i][j] = DOMINATED; // Cover dominated cells
   }
   for(int i = row, j = col; i < N && j >= 0; ++i, --j) {
      if(matrix[i][j] == FREE_SQUARE) matrix[i][j] = DOMINATED;
   }
   for(int i = row, j = col; i >= 0 && j < N; --i, ++j) {
      if(matrix[i][j] == FREE_SQUARE) matrix[i][j] = DOMINATED;
   }
   for(int i = row, j = col; i < N && j < N; ++i, ++j) {
      if(matrix[i][j] == FREE_SQUARE) matrix[i][j] = DOMINATED;
   }
}
   
void printStep(int row, int col, int placedBishopAmount, bool isWhite, bool isValid, FILE *longFile) {
   char depth[N] = "\0";
   char buffer[100];
   //int len = 0;

   for(int i = 1; i < placedBishopAmount; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "\n%6lld)  %s%c%d. Col=%d. Row=%d. %s", ++step, depth, (isWhite ? 'B' : 'J'), placedBishopAmount, col+1, row+1, (isValid ? "Gilyn." : "Netinka."));

   printf("%s", buffer);
   //fprintf(longFile, "%s", buffer);
}

bool recursion(int row, int col, int matrix[N][N], int placedBishopAmount, bool isWhite, FILE *longFile) {
   
   bool isDominated = isBoardDominated(matrix, isWhite);
   if(row >= N || placedBishopAmount >= BISHOP_AMOUNT / 2) {
      if(isDominated) {
         printf("\nPavyko!\n");
         if(isWhite) recursion(0, 1, matrix, 0, false, longFile);
         return true;
      }
      else {
         // printf(" Backtrack.");
         // return false;
      }
   }
   else {
      for(int i = row; i < N; ++i) {
         for(int j = col; j < N; j += 2) {

            if(isWhite && (i + j) % 2 == 0) {
               bool isValid = matrix[i][j] == FREE_SQUARE;
               int previousMatrix[N][N];
               if(isValid) {
                  memcpy(previousMatrix, matrix, sizeof(matrix[0]) * N);
                  ++placedBishopAmount;
                  placeBishop(i, j, matrix);
               }
               printStep(i, j, placedBishopAmount, isWhite, isValid, longFile);
               
               if(recursion(i, j + 2, matrix, placedBishopAmount, isWhite, longFile)) return true;
               printf(" Backtrack.");
               memcpy(matrix, previousMatrix, sizeof(matrix[0]) * N);
               --placedBishopAmount;
            }   
         }
         if(isWhite) col = (row + 1) % 2;
         else col = row % 2;
      }
   }
   return false;
}

// TODO: Make it start checking for white after checking all black
// TODO: Make it find all possible variantions, not just the first one