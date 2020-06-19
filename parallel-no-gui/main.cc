#include"AC.h"
#include<mpi.h>

int main(int argc, char const *argv[]) {

//	printf("Does this even start?\n");

	if(argc < 2) {
		fprintf(stderr, "Usage: matrix-dimension iterations-number\n");
	}

//	printf("Before argc parsing\n");

	const int dim = atoi(argv[1]);
	const int iter = atoi(argv[2]);

	MPI_Init(NULL, NULL);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    srand(time(NULL) * world_rank);

	Cell **mat = NULL;
	Cell **tam = NULL;
	Cell *matdata, *tamdata;
	Cell *sendbufp = NULL;
	
	int p = dim/world_size;

//	printf("Before vec_t commit\n");

	MPI_Datatype vec_t;
	MPI_Type_contiguous(dim, MPI_INT, &vec_t);
	MPI_Type_commit(&vec_t); 

//	printf("Before allocation\n");

	int extra = 0;
	allocateMatrix(&mat, dim, &matdata, dim);
    if(world_rank == 0) {
    	extra = dim - p*world_size;
    	allocateMatrix(&tam, p + extra, &tamdata, dim);
    	sendbufp = &( mat[ extra ][ 0 ] );
    } else {
    	allocateMatrix(&tam, p, &tamdata, dim);
    }

//  printf("Before execution\n");
    
/*    if(world_rank == 0) {
    	printMatrix(mat, dim);
    }
*/
    for(int i = 0; i < iter; ++i) {  
//    	printf("loop no.%d proc %d\n", i, world_rank);
    	MPI_Barrier(MPI_COMM_WORLD);
    	MPI_Bcast((void*)&(mat[0][0]), dim*dim, vec_t, 0, MPI_COMM_WORLD);
//    	printf("Before runWator()\n");
    	runWator(mat, tam, p + extra, dim, p*world_rank, 0);
//    	printf("before MPI_Gather\n");
    	MPI_Gather((void*)&(tam[0][0]), p, vec_t, (void*)sendbufp, p, vec_t, 0, MPI_COMM_WORLD);
//    	if(world_rank == 0)		printMatrix(mat, dim);
    	MPI_Barrier(MPI_COMM_WORLD);
/*    	if(world_rank == 0)
    		printf("\nbefore next iteration\n");
    	if(world_rank == 0) {
    		printMatrix(mat, dim);
    	}
*/    	MPI_Barrier(MPI_COMM_WORLD);
    }
    
	freeMatrix(mat, matdata);
    freeMatrix(tam, tamdata);
    
    MPI_Finalize();
	return 0;
}