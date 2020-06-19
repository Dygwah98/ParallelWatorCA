#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<cmath>
#include<mpi.h>

typedef int Cell;

typedef struct {
	int i;
	int j;
} CellKey;

const int key[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

//matrix indexed by key[i][j] and containing id values
const int value_original[10][10] = {
       //0 10 11 12 20 21 22 30 31 32
/*0*/	{0, 0, 1, 1, 0, 2, 2, 0, 3, 3},
/*10*/	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
/*11*/	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
/*12*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*20*/	{2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
/*21*/	{2, 2, 2, 2, 2, 0, 0, 0, 0, 0},
/*22*/	{0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
/*30*/	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
/*31*/	{3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
/*32*/	{0, 3, 3, 3, 3, 3, 3, 3, 0, 0}
	};

void allocateMatrix(Cell ***datap, const int n, Cell** data, const int dim);
void freeMatrix(Cell** p, Cell* data);
CellKey calculateCellKey(const Cell& cell);
Cell* chooseNeighbor(int pi, int pj, int& i, int& j, const int dim);
void transition(Cell& cell, Cell& neighbor, Cell& newcell);
void printMatrix(Cell** mat, const int dim);
void runWator(Cell** mat, Cell** tam, const int p, const int dim, const int sx, const int sy);