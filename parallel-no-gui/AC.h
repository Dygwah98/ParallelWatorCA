#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<cmath>
#include<mpi.h>
#include<omp.h>

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
inline CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell/100 - 1;
	static int jmap[3][2] = {{8,15}, {3,5}, {2,7}};

	ret.j = (cell%100 == jmap[ret.i][1]) ? 2 : (cell%100 > jmap[ret.i][0]) ? 1 : 0;
	return ret;
}
inline Cell* chooseNeighbor(int pi, int pj, const int dim, Cell** mat) {

	int pos[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
	int pivot = rand()%8;

	int temp = (pi*dim + pj);
	int i = (temp/dim + pos[pivot]/3 + dim) % dim;
	int j = (temp%dim + pos[pivot]%3 + dim) % dim;

	return &(mat[i][j]);
}
inline void transition(Cell& cell, Cell& neighbor, Cell& newcell) {

	int i = 0;
	int j = 0;
	CellKey key1 = {0, 0};
	CellKey key2 = {0, 0};
	if(cell/100 != 0) {
		key1 = calculateCellKey(cell);
		i = key[key1.i][key1.j];
	}
	if(neighbor/100 != 0) {
		key2 = calculateCellKey(neighbor);
		j = key[key2.i][key2.j];
	}

	newcell = value_original[i][j]*100;
	newcell += (key1.j == 2 || newcell/100 == 0) ? 0 : cell%100 + 1;

}
void printMatrix(Cell** mat, const int dim);