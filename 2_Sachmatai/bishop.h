#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define N 5
#define BISHOP_AMOUNT 6

// Board cell states
#define FREE_SQUARE 0
#define STANDING 1 
#define DOMINATED 2

extern long long step;
extern long long amount;

bool isBoardDominated(int matrix[N][N], bool isWhite);

bool isValidPlacement(int col, int row, int matrix[N][N]);

void placeBishop(int col, int row, int matrix[N][N]);

void printStep(int col, int row, int placedBishopAmount, bool isWhite, bool isValid, FILE *longFile);

bool recursion(int col, int row, int matrix[N][N], int placedBishopAmount, bool isWhite, FILE *longFile);


#endif