#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>

#define BISHOP_AMOUNT 8
#define AMOUNT_OF_ANSWERS 10

// Board cell states
#define FREE_SQUARE 0
#define STANDING 1 
#define DOMINATED 2

extern long long step;
extern long long amount;
extern int N;

void print(char *buffer, FILE *outputFile);

char *reverseRow(char *row);

void printBoard(unsigned matrix[N][N], FILE *outputFile, int num);

bool isBoardDominated(unsigned matrix[N][N], bool isBlack);

bool isValidPlacement(unsigned col, unsigned row, unsigned matrix[N][N]);

void placeBishop(unsigned col, unsigned row, unsigned matrix[N][N]);

void printStep(unsigned col, unsigned row, unsigned placedBishopAmount, bool isBlack, bool isValid, FILE *outputFile);

void solve(unsigned row, unsigned col, unsigned matrix[N][N], unsigned answer[3][N][N], unsigned placedBishopAmount, bool isBlack, FILE *outputFile);

#endif