#include"AC.h"

void allocateMatrices(Cell*** mat, Cell*** tam, const int& dim) {

	*mat = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		(*mat)[i] = new Cell[dim];
		for(int j = 0; j < dim; ++j) {
			(*mat)[i][j].id = rand()%4;
			(*mat)[i][j].age = 0;
		}
	}

	*tam = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		(*tam)[i] = new Cell[dim];
		for(int j = 0; j < dim; ++j) {
			(*tam)[i][j].id  = (*mat)[i][j].id;
			(*tam)[i][j].age = (*mat)[i][j].age;
		}
	}
}

void freeMatrices(Cell*** mat, Cell*** tam, const int& dim) {

	for(int i = 0; i < dim; ++i)
		delete (*mat)[i];
	delete (*mat);

	for(int i = 0; i < dim; ++i)
		delete (*tam)[i];
	delete (*tam);

}

CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell.id - 1;
	int jmap[3][2] = {{8,15}, {3,5}, {2,7}};

	ret.j = (cell.age == jmap[ret.i][1]) ? 2 : (cell.age > jmap[ret.i][0]) ? 1 : 0;

	return ret;
}

void chooseNeighbor(int pi, int pj, int& i, int& j, Cell** mat, const int dim) {

	static int pos[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
	int pivot = rand()%8;

	int temp = (pi*dim + pj + pos[pivot]);
	i = (temp/dim)%dim;
	j = (temp + dim)%dim;
}

void transition(Cell& cell, Cell& neighbor, Cell& newcell) {

	//printf("starting transition({%d},{%d}...\n", cell.id, neighbor.id);

	CellKey key1 = calculateCellKey(cell);
	CellKey key2 = calculateCellKey(neighbor);

	int i = key[key1.i][key1.j];
	int j = key[key2.i][key2.j];

	newcell.id = value_original[i][j];
	newcell.age = (key1.j == 2 || newcell.id == 0) ? 0 : cell.age + 1;
}

void printMatrix(Cell** mat, const int dim) {

	int pop[4] = {0, 0, 0, 0};

	for(int i = 0; i < dim; ++i) {

		printf("\n");
		
		for(int j = 0; j < dim; ++j) {
			printf("%d ", mat[i][j].id);
			++pop[ mat[i][j].id ];
		}
	}
	printf("\n\n");
	printf("Sharks: %d\nFishes: %d\nShrimps: %d\n", pop[3], pop[2], pop[1]);
	printf("\n");
}

void runWator(Cell*** mat, Cell*** tam, const int& dim) {

	int x, y;
    for(int i = 0; i < dim; ++i) {
        for(int j = 0; j < dim; ++j) {

//				printf("iteration %d index %d %d\n", it, i, j);

            if((*mat)[i][j].id != 0) {
                chooseNeighbor(i, j, x, y, *mat, dim);
                transition((*mat)[i][j], (*mat)[x][y], (*tam)[i][j]);
            }
        }
    }

    std::swap(mat, tam);
}
