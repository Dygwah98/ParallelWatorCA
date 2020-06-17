#include"../headers/AC.h"

int main(int argc, char const *argv[]) {

	const int dim = 25;
	srand(time(NULL));

	Cell** mat = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		mat[i] = new Cell[dim];
		for(int j = 0; j < dim; ++j) {
			mat[i][j].id = rand()%4;
			mat[i][j].age = 0;
		}
	}

	Cell** tam = new Cell*[dim];
	for(int i = 0; i < dim; ++i) {
		tam[i] = new Cell[dim];
		for(int j = 0; j < dim; ++j) {
			tam[i][j].id = mat[i][j].id;
			tam[i][j].age = mat[i][j].age;
		}
	}

	int x, y;
	for(int it = 0; it < 10; ++it) {
		
		printMatrix(mat, dim);

		for(int i = 0; i < dim; ++i) {
			for(int j = 0; j < dim; ++j) {

//				printf("iteration %d index %d %d\n", it, i, j);

				if(mat[i][j].id != 0) {
					chooseNeigbor(i, j, x, y, mat, dim);
					transition(mat[i][j], mat[x][y], tam[i][j]);
				}
			}
		}

		std::swap(mat, tam);
	}

	for(int i = 0; i < dim; ++i)
		delete mat[i];
	delete mat; 


	for(int i = 0; i < dim; ++i)
		delete tam[i];
	delete tam; 

	return 0;
}