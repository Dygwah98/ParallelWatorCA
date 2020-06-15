#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>

typedef struct {
	int id;
	int age;
} Cell;

typedef struct {
	int i;
	int j;
} CellKey;

//	int key[] = {0, 10, 11, 12, 20, 21, 22, 30, 31, 32};
	const int key[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	//these two matrices are indexed by keys and contain id values
	const int value_original[10][10] = {
	   //0 10 11 12 20 21 22 30 31 32
/*0*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*10*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*11*/	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*12*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*20*/	{0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*21*/	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*22*/	{0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*30*/	{0, 3, 3, 3, 3, 3, 3, 0, 0, 0},
/*31*/	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
/*32*/	{0, 3, 3, 3, 3, 3, 3, 3, 3, 3}
	};
	const int value_neighbor[10][10] = {
	   //0 10 11 12 20 21 22 30 31 32
/*0*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*10*/	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*11*/	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*12*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*20*/	{2, 0, 0, 0, 2, 2, 2, 0, 0, 0},
/*21*/	{2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*22*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*30*/	{3, 0, 0, 0, 0, 0, 0, 3, 3, 3},
/*31*/	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*32*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell.id - 1;
	if(cell.id == 1) {

		ret.j = (cell.age == 15) ? 2 : (cell.age%13)/8;

	} else if(cell.id == 2) {

		ret.j = (cell.age == 5) ? 2 : cell.age/3;

	} else if(cell.id == 3) {

		ret.j = (cell.age == 7) ? 2 : (cell.age > 1) ? 1 : 0;

	}
}

void transition(Cell& cell, cell& neighbor) {

	CellKey key1 = calculateCellKey(cell);
	CellKey key2 = calculateCellKey(neighbor);

	cell.id = value_original[key1.i][key1.j];
	if(key1.j != 2)
		++cell.age;
	else 
		cell.age = 0;
	neighbor.id = value_neighbor[key2.i][key2.j];
	if(key2.j != 2)
		++neigbhor.age;
	else 
		neighbor.age = 0;
}

int main(int argc, char const *argv[]) {

	return 0;
}