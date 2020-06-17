#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>

typedef struct {
	int id;
	int age;
} Cell;

typedef struct {
	int i;
	int j;
} CellKey;

const int key[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	//these two matrices are indexed by keys and contain id values
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

CellKey calculateCellKey(const Cell& cell);
void chooseNeigbor(int pi, int pj, int& i, int& j, Cell** mat, const int dim);
void transition(Cell& cell, Cell& neighbor, Cell& newcell);
void printMatrix(Cell** mat, const int dim);