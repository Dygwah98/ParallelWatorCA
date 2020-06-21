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