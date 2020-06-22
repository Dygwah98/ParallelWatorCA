#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<cmath>
#include<mpi.h>
#include<omp.h>

typedef int Cell;

void allocateMatrix(Cell ***datap, const int n, Cell** data, const int dim, unsigned& seed);
void freeMatrix(Cell** p, Cell* data);

void printMatrix(Cell** mat, const int dim);

inline unsigned int my_rand_r(unsigned int* seed) {

	unsigned int next = *seed;

	next *= 1103515245U;
	next += 12345U;
	*seed = next;

	return (next / 65536U) % RAND_MAX;
}