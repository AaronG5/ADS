#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define N 4
#define BISHOP_AMOUNT 4

#define FREE_SQUARE 0
#define STANDING 1 
#define DOMINATED 2

extern int step;
extern int amount;

bool isBoardDominated(int matrix[N][N], bool isWhite);

bool isValidPlacement(int col, int row, int matrix[N][N]);

void placeBishop(int col, int row, int matrix[N][N]);

void printStep(int col, int row, int placedBishopAmount, bool isWhite, FILE *longFile);

void recursion(int col, int row, int matrix[N][N], int placedBishopAmount, bool isWhite, FILE *longFile);


#endif