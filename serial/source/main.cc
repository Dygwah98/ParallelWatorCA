#include"../headers/AC.h"

int main(int argc, char const *argv[]) {

	srand(time(NULL));

	const int dim = 25;
	Cell **mat;
	Cell **tam;

	allocateMatrices(&mat, &tam, dim);

	runWator(mat, tam, dim);

	freeMatrices(&mat, &tam, dim);	

	return 0;
}