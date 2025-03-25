#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define N 9
#define BISHOP_AMOUNT 8

// Board cell states
#define FREE_SQUARE 0
#define STANDING 1 
#define DOMINATED 2

extern long long step;
extern long long amount;

void printBoard(unsigned matrix[N][N], FILE *shortFile, FILE *longFile);

bool isBoardDominated(unsigned matrix[N][N], bool isBlack);

bool isValidPlacement(unsigned col, unsigned row, unsigned matrix[N][N]);

void placeBishop(unsigned col, unsigned row, unsigned matrix[N][N]);

void printStep(unsigned col, unsigned row, unsigned placedBishopAmount, bool isBlack, bool isValid, FILE *longFile);

void solve(unsigned col, unsigned row, unsigned matrix[N][N], unsigned answer[2][N][N], unsigned placedBishopAmount, bool isBlack, FILE *longFile);

#endif