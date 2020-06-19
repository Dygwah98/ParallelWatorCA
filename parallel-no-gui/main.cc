#include"AC.h"
#include<mpi.h>

int main(int argc, char const *argv[]) {

	if(argc < 2) {
		fprintf(stderr, "Usage: matrix-dimension iterations-number\n");
	}

	const int dim = atoi(argv[1]);
	const int iter = atoi(argv[2]);

	MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    srand(time(NULL) * world_rank);

	Cell **mat, **tam;
	
	int partition = getPartitionSize(dim, world_size);

    if(world_rank == 0) {
    	allocateMatrices(&mat, &tam, dim);
    }

	//runWator(&mat, &tam, dim, iter, &ghostcells);

	if(world_rank == 0) {
		freeMatrices(&mat, &tam, dim);
    }
    
	MPI_Finalize();
	return 0;
}