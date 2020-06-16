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
/*10*/	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/*11*/	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/*12*/	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/*20*/	{0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*21*/	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*22*/	{0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
/*30*/	{0, 3, 3, 3, 3, 3, 3, 3, 3, 3},
/*31*/	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
/*32*/	{0, 3, 3, 3, 3, 3, 3, 3, 3, 3}
	};
	const int value_neighbor[10][10] = {
	   //0 10 11 12 20 21 22 30 31 32
/*0*/	{0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
/*10*/	{1, 1, 1, 1, 2, 2, 2, 3, 3, 3},
/*11*/	{1, 1, 1, 1, 2, 2, 2, 3, 3, 3},
/*12*/	{0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
/*20*/	{2, 0, 0, 0, 2, 2, 2, 3, 3, 3},
/*21*/	{2, 0, 0, 0, 0, 0, 0, 3, 3, 3},
/*22*/	{0, 0, 0, 0, 0, 0, 0, 3, 3, 3},
/*30*/	{3, 0, 0, 0, 0, 0, 0, 3, 3, 3},
/*31*/	{3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*32*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

inline CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell.id - 1;
	if(cell.id == 1) {

		ret.j = (cell.age == 15) ? 2 : (cell.age%13)/8;

	} else if(cell.id == 2) {

		ret.j = (cell.age == 5) ? 2 : cell.age/3;

	} else if(cell.id == 3) {

		ret.j = (cell.age == 7) ? 2 : (cell.age > 1) ? 1 : 0;

	} else {

		ret.j = 0;
	}

	return ret;
}

void chooseNeigbor(int pi, int pj, int& i, int& j, Cell** mat, const int dim) {

//	printf("starting chooseNeigbor(%d,%d,%d,%d,%d...\n", pi, pj,i,j, mat);

	int posi = rand()%3;
	int posj = rand()%3;
	if(posi == 1 && posj == 1) {
		posi = posj = 0;
	}
	int si = (pi-1 + dim) % dim;
	int sj = (pj-1 + dim) % dim;
	
	i = (si + posi) % dim;
	j = (sj + posj) % dim;				

//	printf("Before id check\n");

	//if a shrimp
	if(mat[pi][pj].id == 1) {
		
//		printf("First id check, i: %d j: %d\n", i, j);

		if(mat[i][j].id != 0)
		for(int ind = 0; ind < 3; ++ind) {
//			printf("       posi %d posj %d\n", posi, posj);
			for(int ind2 = 0; ind2 < 3; ++ind2) {
				posj = (posj + 1) % 3;
				if(mat[(si + posi) % dim][(sj + posj) % dim].id == 0 && posi != 1 && posj != 1) {
					i = (si + posi) % dim;
					j = (sj + posj) % dim;
//					printf("Returning %d %d at %d %d\n", i, j, ind, ind2);
					return;
				}
			}
			posi = (posi + 1) % 3;
			if(posi == 0)
				posj = 0;
		}
	//if a fish
	} else if(mat[pi][pj].id == 2) {

//		printf("Second id check, i: %d j: %d\n", i, j);

		if(mat[i][j].id == 3)
		for(int ind = 0; ind < 3; ++ind) {
			for(int ind2 = 0; ind2 < 3; ++ind2) {
				posj = (posj + 1) % 3;
				if(mat[(si + posi) % dim][(sj + posj) % dim].id == 0 && posi != 1 && posj != 1) {
					i = (si + posi) % dim;
					j = (sj + posj) % dim;
//					printf("Returning %d %d at %d %d\n", i, j, ind, ind2);
					return;
				}
			}
			posi = (posi + 1) % 3;
		}
	}

//	printf("Returning %d %d at end\n", i, j);
}

inline void transition(Cell& cell, Cell& neighbor, Cell& newcell, Cell& newneighbor) {

//	printf("starting transition({%d},{%d}...\n", cell.id, neighbor.id);

	CellKey key1 = calculateCellKey(cell);
	CellKey key2 = calculateCellKey(neighbor);

	int i = key[key1.i][key1.j];
	int j = key[key2.i][key2.j];

	newcell.id = value_original[i][j];
	newneighbor.id = value_neighbor[i][j];
	newcell.age = (key1.j == 2) ? 0 : cell.age + 1;
	newneighbor.age = (key2.j == 2) ? 0 : cell.age + 1;
}

void printMatrix(Cell** mat, const int dim) {

	for(int i = 0; i < dim; ++i) {
		for(int j = 0; j < dim; ++j) {
			printf("%d ", mat[i][j].id);
		}
		printf("\n");
	}
	printf("\n\n");
}

bool canUpdate(int i, int j, int x, int y, int dim, const std::set<int>& tat) {

	return x != -1 && y != -1
		&& tat.find(x*dim + y) == tat.end()
		&& tat.find(i*dim + j) == tat.end();
}

int main(int argc, char const *argv[]) {

	const int dim = 5;
	srand(time(NULL));

	Cell** mat = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		mat[i] = new Cell[dim];
		for(int j = 0; j < dim; ++j) {
			mat[i][j].id = rand()%2;
			mat[i][j].age = 0;
		}
	}

	Cell** tam = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		tam[i] = new Cell[dim];
	}

	int x, y;
	std::set<int> tat;
	for(int it = 0; it < 5; ++it) {
		
		printMatrix(mat, dim);

		for(int i = 0; i < dim; ++i) {
			for(int j = 0; j < dim; ++j) {

//				printf("iteration %d index %d %d\n", it, i, j);

				if(mat[i][j].id != 0) {
					x = y = -1;			
					chooseNeigbor(i, j, x, y, mat, dim);
					if(canUpdate(i, j, x, y, dim, tat)) {
						transition(mat[i][j], mat[x][y], tam[i][j], tam[x][y]);
						tat.insert(i*dim+j);
						tat.insert(x*dim+y);
					}
				}
			}
		}

		std::swap(mat, tam);
		tat.clear();
	}


	for(int i = 0; i < dim; ++i)
		delete mat[i];
	delete mat; 


	for(int i = 0; i < dim; ++i)
		delete tam[i];
	delete tam; 

	return 0;
}