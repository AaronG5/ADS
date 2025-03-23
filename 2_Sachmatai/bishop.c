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

bool isValidPlacement(int col, int row, int matrix[N][N]) {
   if(matrix[col][row] == FREE_SQUARE) {
      return true;
   }
   return false;
}

void placeBishop(int col, int row, int matrix[N][N]) {
   matrix[col][row] = STANDING; // Place bishop

   for(int i = col, j = row; i >= 0 && j >= 0; --i, --j) {
      if(matrix[i][j] == FREE_SQUARE) {
         matrix[i][j] = DOMINATED; // Cover dominated cells
      }
   }
   for(int i = col, j = row; i < N && j >= 0; ++i, --j) {
      if(matrix[i][j] == FREE_SQUARE) {
         matrix[i][j] = DOMINATED;
      }
   }
   for(int i = col, j = row; i >= 0 && j < N; --i, ++j) {
      if(matrix[i][j] == FREE_SQUARE) {
         matrix[i][j] = DOMINATED;
      }
   }
   for(int i = col, j = row; i < N && j < N; ++i, ++j) {
      if(matrix[i][j] == FREE_SQUARE) {
         matrix[i][j] = DOMINATED;
      }
   }
}

void removeBishop(int col, int row, int matrix[N][N]) {
   matrix[col][row] = FREE_SQUARE; // Remove bishop

   for(int i = col, j = row; i >= 0 && j >= 0; --i, --j) {
      if(matrix[i][j] == DOMINATED) {
         matrix[i][j] = FREE_SQUARE; // Uncover dominated cells
      }
   }
   for(int i = col, j = row; i < N && j >= 0; ++i, --j) {
      if(matrix[i][j] == DOMINATED) {
         matrix[i][j] = FREE_SQUARE;
      }
   }
   for(int i = col, j = row; i >= 0 && j < N; --i, ++j) {
      if(matrix[i][j] == DOMINATED) {
         matrix[i][j] = FREE_SQUARE;
      }
   }
   for(int i = col, j = row; i < N && j < N; ++i, ++j) {
      if(matrix[i][j] == DOMINATED) {
         matrix[i][j] = FREE_SQUARE;
      }
   }
}
   

void printStep(int col, int row, int placedBishopAmount, bool isWhite, bool isValid, FILE *longFile) {
   char depth[N] = "\0";
   char buffer[100];
   //int len = 0;

   for(int i = 1; i < placedBishopAmount; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "\n%6d)  %s%c%d. Col=%d. Row=%d. %s", ++step, depth, (isWhite ? 'B' : 'J'), placedBishopAmount, col+1, row+1, (isValid ? "Gilyn." : "Netinka."));

   printf("%s", buffer);
   //fprintf(longFile, "%s", buffer);
}

bool recursion(int col, int row, int matrix[N][N], int placedBishopAmount, bool isWhite, FILE *longFile) {
   
   bool isDominated = isBoardDominated(matrix, isWhite);
   if((row >= N || placedBishopAmount >= BISHOP_AMOUNT / 2) && !isDominated) {
      printf(" Backtrack.");
      return false;
   }

   if(isDominated && placedBishopAmount == BISHOP_AMOUNT / 2) {
      printf("\nPavyko!\n");
      if(isWhite) {
         recursion(1, 0, matrix, 0, false, longFile);
      }
      return true;
   }

   bool isValid = isValidPlacement(col, row, matrix);
   if(isValid) {
      placeBishop(col, row, matrix);
      ++placedBishopAmount;
   }
   printStep(col, row, placedBishopAmount, isWhite, isValid, longFile);

   //printStep(col, row, placedBishopAmount, isWhite, longFile);
   
   if (col + 2 < N) {
      if(recursion(col + 2, row, matrix, placedBishopAmount, isWhite, longFile)) {
         return true;
      }
      else {
         return false;
      }
   }
   // If we finished a row, move to the next row
   else {
      if(isWhite) {
         if(recursion((row + 1) % 2, row + 1, matrix, placedBishopAmount, isWhite, longFile)) {  // Start at (0, j + 1) or (1, j + 1)
            return true;
         }
         else {
            removeBishop(col, row, matrix);
            --placedBishopAmount;
            return false;
         }
      }
      else {
         if(recursion(row % 2, row + 1, matrix, placedBishopAmount, isWhite, longFile)) {
            return true;
         }
         else {
            removeBishop(col, row, matrix);
            --placedBishopAmount;
            return false;
         }
      }
   }
}