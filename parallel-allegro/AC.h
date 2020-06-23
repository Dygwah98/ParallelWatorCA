#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<set>
#include<cmath>
#include<mpi.h>
#include<omp.h>
#include<algorithm>
#include<random>

typedef int Cell;

void allocateMatrix(Cell ***datap, const int n, Cell** data, const int dim, unsigned& seed);
void freeMatrix(Cell** p, Cell* data);

void printMatrix(Cell** mat, const int dim);

inline unsigned int my_rand_r(unsigned int* seed) {

   	*seed = (*seed) * 1103515245 + 12345; 

  	return (unsigned int)((*seed)/65536) % RAND_MAX; 
}