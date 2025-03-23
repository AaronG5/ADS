#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

// TODO: make it check for limit of bishop pieces (8)

#define N 4
#define BISHOP_AMOUNT 4

// States of chess board cells
#define FREE_SQUARE 0
#define STANDING 1 
#define DOMINATED 2

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

void printStep(int col, int row, int placedBishopAmount, bool isWhite, FILE *longFile) {
   char depth[N] = "\0";
   char buffer[150];
   //int len = 0;

   for(int i = 0; i < placedBishopAmount; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "\n%6d)  %sR%d. Col=%d. Row=%d.", ++step, depth, placedBishopAmount, col, row);

   printf("%s", buffer);
   //fprintf(longFile, "%s", buffer);
}

void recursion(int col, int row, int matrix[N][N], int placedBishopAmount, bool isWhite, FILE *longFile) {
   
   if(row > N || placedBishopAmount >= BISHOP_AMOUNT) {
      return;
   }

   if(isBoardDominated(matrix, isWhite)) {
      return;
   }

   if(isValidPlacement(col, row, matrix)) {
      placeBishop(col, row, matrix);
      ++placedBishopAmount;
      printStep(col, row, placedBishopAmount, isWhite, longFile);
   }

   //printStep(col, row, placedBishopAmount, isWhite, longFile);
   
   if (col + 2 < N) {
      recursion(col + 2, row, matrix, placedBishopAmount, (isWhite ? true : false), longFile);
   }
   // If we finished a row, move to the next row
   else {
      if(isWhite) {
         recursion((row + 1) % 2, row + 1, matrix, placedBishopAmount, (isWhite ? true : false), longFile);  // Start at (0, j + 1) or (1, j + 1)
      }
      else {
         recursion(row % 2, row + 1, matrix, placedBishopAmount, (isWhite ? true : false), longFile);
      }
   }
   

   // Tikriname kiekviena karta kai
   // for(int i = 0, j = 0; i < N; --i, --j) {
   //    if(matrix[i][j]) {
   //       return false; // cant place here
   //    }
   // }
   // and so on with ++i, --j;  --i, ++j;  ++i, ++j;

   // Check if board is dominated:
   // for(int i = 0; i < N; ++i) {
   //    for(int j = 0; j < N; ++j) {
   //       if(!matrix[i][j]) {
   //          return false; // Not dominated
   //       }
   //    }
   // }
   
   
   
   // bool deeper;
   // int oldAmount = amount;


   // if(row == N) {
   //    printf("End reached! ");
   //    fprintf(longFile, "End reached! ");
   //    for(int i = 0; i < row; ++i) {
   //       printf("%c ", combination[i] + 65);
   //       fprintf(longFile, "%c ", combination[i] + 65);
   //    }
   //    ++amount;
   //    return;
   // }

   // for(int i = 0; i < N; ++i) {
   //    deeper = true;

      
   //    // if(usedCol[i]) {
   //    //    deeper = false;
   //    // }

   //    stepInfo(buffer, row + 1, i + 1, deeper, false, longFile);
      
   //    if(deeper) {
   //       //usedCol[i] = true;
   //       combination[row] = i;
   //       recursion(row+1, combination, buffer, longFile);
   //       // usedCol[i] = false;
   //    }
   // }
   // if(oldAmount < amount) {
   //    printf("Backtrack. ");
   //    fprintf(longFile, "Backtrack. ");
   // }
}

