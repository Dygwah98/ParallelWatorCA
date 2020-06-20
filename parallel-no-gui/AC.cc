#include"AC.h"

void allocateMatrix(Cell ***datap, const int n, Cell** data, const int dim) {

	(*data) = new Cell[n*dim];
	for(int i = 0; i < n*dim; ++i)
		(*data)[i] = (rand()%4)*100;


	(*datap) = new Cell*[n];
	for(int i = 0; i < n; ++i)
		(*datap)[i] = (*data) + i*dim;

}

void freeMatrix(Cell** p, Cell* data) {

	delete[] data;
	delete[] p;
}

CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell/100 - 1;
	static int jmap[3][2] = {{8,15}, {3,5}, {2,7}};

	ret.j = (cell%100 == jmap[ret.i][1]) ? 2 : (cell%100 > jmap[ret.i][0]) ? 1 : 0;
	return ret;
}

Cell* chooseNeighbor(int pi, int pj, const int dim, Cell **mat) {

	int pos[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
	int pivot = rand()%8;

	int temp = (pi*dim + pj);
	int i = (temp/dim + pos[pivot]/3 + dim) % dim;
	int j = (temp%dim + pos[pivot]%3 + dim) % dim;

	return &(mat[i][j]);
}

void transition(Cell& cell, Cell& neighbor, Cell& newcell) {

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

void printMatrix(Cell** mat, const int dim) {

	int pop[4] = {0, 0, 0, 0};

	for(int i = 0; i < dim; ++i) {

		printf("\n");
		
		for(int j = 0; j < dim; ++j) {
			printf("%d ", mat[i][j]/100);
			++pop[ mat[i][j]/100 ];
		}
	}
	printf("\n\n");
	printf("Sharks: %d\nFishes: %d\nShrimps: %d\n", pop[3], pop[2], pop[1]);
	printf("\n");
}

void printInfo(Cell** mat, const int dim, int it) {
	
	int pop[4] = {0, 0, 0, 0};

	for(int i = 0; i < dim; ++i)
		for(int j = 0; j < dim; ++j)
			++pop[ mat[i][j]/100 ];
	
	printf("\n");
	printf("Iteration: %d ", it);
	printf("Sharks: %d Fishes: %d Shrimps: %d\n", pop[3], pop[2], pop[1]);
	printf("\n");
}

void runWator(Cell** mat, Cell** tam, const int p, const int dim, const int sx, const int sy) {

	Cell* neighbor;
	
	#pragma omp parallel for shared(mat, tam)
    for(int i = 0; i < p; ++i) {
        int si = sx + i;
        for(int j = 0; j < dim; ++j) {
			int sj = sy + j;
			neighbor = chooseNeighbor(si, sj, dim, mat);
            transition(mat[si][sj], *neighbor, tam[i][j]);
        }
    }
}