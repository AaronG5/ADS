#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bishop.h"

void print(char *buffer, FILE *outputFile) {
   printf("%s", buffer);
   fprintf(outputFile, "%s", buffer);
}

char *reverseRow(char *row) {
   int left = 0;
   int right = strlen(row) - 1;

   while(left < right) {
      char temp = row[left];
      row[left] = row[right];
      row[right] = temp;
      ++left;
      --right;
   }
   return row;
}

void printBoard(unsigned matrix[N][N], FILE *outputFile, int num) {
   char buffer[1000] = "\0";
   char temp[10];
   int whiteBishopAmount = 4, blackBishopAmount = 4;
   if(num > 0) {
      sprintf(buffer, "\nSprendinys Nr. %d", num);
   }
   for(int i = N-1; i >= 0; --i) {
      char invertedRow[100] = "\0";
      strcat(buffer, "\n  +");

      for(int j = 0; j < N; ++j) {
         strcat(buffer, "----+");
      }
      
      sprintf(temp, "\n%d |", i+1);
      strcat(buffer, temp);

      if(isBoardDominated(matrix, true)) {
         for(int j = N-1; j >= 0; --j) {
            if((i + j) % 2 == 0 && matrix[i][j] == STANDING) {
               sprintf(temp, "| %dJ ", blackBishopAmount--);
               strcat(invertedRow, temp);
            }
            else if((i + j) % 2 == 1 && matrix[i][j] == STANDING) {
               sprintf(temp, "| %dB ", whiteBishopAmount--);
               strcat(invertedRow, temp);
            }
            else {
               strcat(invertedRow, "|    ");
            }
         }
         strcat(buffer, reverseRow(invertedRow));
      }
      else {
         for(int j = 0; j < N; ++j) {
            strcat(buffer, "    |");
         }
      }
   }
   strcat(buffer, "\n  +");

   for(int j = 0; j < N; ++j) {
      strcat(buffer, "----+");
   }
   strcat(buffer, "\n");
   strcat(buffer, "  ");

   for(int j = 0; j < N; ++j) {
      sprintf(temp, "  %c  ", j + 65);
      strcat(buffer, temp);
   }
   printf("%s\n", buffer);
   fprintf(outputFile, "%s\n", buffer);
}

bool isBoardDominated(unsigned matrix[N][N], bool isBlack) {
   for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
         if(isBlack && (i + j) % 2 == 0 && matrix[i][j] == FREE_SQUARE) {
            return false;
         }
         if(!isBlack && (i + j) % 2 == 1 && matrix[i][j] == FREE_SQUARE) {
            return false;
         }
      }
   }
   return true;
}

bool isValidPlacement(unsigned row, unsigned col, unsigned matrix[N][N]) {
   if(matrix[row][col] == FREE_SQUARE) {
      printf("Col = %d, Row = %d\n", col, row);
      return true;
   }
   return false;
}

void placeBishop(unsigned row, unsigned col, unsigned matrix[N][N]) {
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
   
void printStep(unsigned row, unsigned col, unsigned placedBishopAmount, bool isBlack, bool isValid, FILE *outputFile) {
   char depth[5] = "\0";
   char buffer[100];
   char statusMsg[10];

   if(!isValid || (row+1 == N && (col+1 == N || col == N))) {
      sprintf(statusMsg, "Netinka");
   }
   else {
      sprintf(statusMsg, "Tinka");
   }

   for(int i = 1; i < placedBishopAmount; ++i) {
      int len = strlen(depth);
      depth[len] = '-';
      depth[len+1] = '\0';
   }

   sprintf(buffer, "\n%7lld) %s%c%d stovi langelyje %c %d. %s", ++step, depth, (isBlack ? 'J' : 'B'), placedBishopAmount, col+65, row+1, statusMsg);

   printf("%s", buffer);
   fprintf(outputFile, "%s", buffer);
}

bool solve(unsigned row, unsigned col, unsigned matrix[N][N], unsigned answer[AMOUNT_OF_ANSWERS][N][N], unsigned placedBishopAmount, bool isBlack, FILE *outputFile) {
   for(int i = row; i < N; ++i) {
      int previousMatrix[N][N];
      for(int j = col; j < N; j += 2) { // Start iterating through chess board

         bool isPlacementValid;
         if(matrix[i][j] == FREE_SQUARE) {
            if(placedBishopAmount < BISHOP_AMOUNT / 2 && i+1 >= N && j+3 >= N) {
               isPlacementValid = false;
            }
            else {
               isPlacementValid = true;
            }
         }
         else {
            isPlacementValid = false;
         }

         if(isPlacementValid) {
            memcpy(previousMatrix, matrix, sizeof(matrix[0]) * N); // Copy board layout
            placeBishop(i, j, matrix);
               
            isPlacementValid = (isBoardDominated(matrix, isBlack)) || (placedBishopAmount != BISHOP_AMOUNT / 2); // Check if board is dominated or amount doesn't exceed max
            if(!isPlacementValid) {
               memcpy(matrix, previousMatrix, sizeof(matrix[0]) * N); // Return board layout if invalid placement
            }
         }

         printStep(i, j, placedBishopAmount, isBlack, isPlacementValid, outputFile);

         if(isBoardDominated(matrix, isBlack) && placedBishopAmount == BISHOP_AMOUNT / 2) {
            if(isBlack) {
               print(" Pavyko. Pereinama i baltu rikiu skaiciavima.", outputFile);
               if(solve(0, 1, matrix, answer, 1, false, outputFile)) return true;
               memcpy(matrix, previousMatrix, sizeof(matrix[0]) * N);
            }
            else {
               if(amount < AMOUNT_OF_ANSWERS) {
                  memcpy(answer[amount], matrix, sizeof(matrix[0]) * N);
               }
               else {
                  return true;
               }
               ++amount;
               printf(" Rastas atsakymas Nr. %lld", amount);
               fprintf(outputFile, " Rastas atsakymas Nr. %lld", amount);
               memcpy(matrix, previousMatrix, sizeof(matrix[0]) * N);
               if(amount == 10) return true;
            }
         }

         if(isPlacementValid && placedBishopAmount != BISHOP_AMOUNT / 2) {
            int oldAmountOfAnswers = amount;
            bool is_B3 = placedBishopAmount == 2;
            if(solve(i, j + 2, matrix, answer, placedBishopAmount + 1, isBlack, outputFile)) return true;
            if((!(i+1 >= N && j+3 >= N) && oldAmountOfAnswers == amount) && !is_B3) {
               print(" BACKTRACK, nesekme. ", outputFile);
            }
            memcpy(matrix, previousMatrix, sizeof(matrix[0]) * N);
         }
      }
      if(isBlack) col = (i + 1) % 2;
      else col = i % 2;
   }
   if(placedBishopAmount == 3) {
      print(" BACKTRACK, nesekme. ", outputFile);
   }
   return false;
}