#include"AC.h"
#include<mpi.h>

int main(int argc, char const *argv[]) {

	if(argc < 3) {
		fprintf(stderr, "Usage: matrix-dimension iterations-number\n");
	}

	int provided = 0;
	MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided);
    if(provided != MPI_THREAD_MULTIPLE) {
    	fprintf(stderr, "not enough multithread support\n");
    	MPI_Abort(MPI_COMM_WORLD,0);
    }
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	double start;
	if(world_rank == 0)
		start = MPI_Wtime();

	const int dim = atoi(argv[1]);
	const int iter = atoi(argv[2]);
	const int nthreads = atoi(argv[3]);

    srand(time(NULL) * world_rank);

	Cell **mat = NULL;
	Cell **tam = NULL;
	Cell *matdata, *tamdata;
	Cell *sendbufp = NULL;
	
	int p = dim/world_size;

	MPI_Datatype vec_t;
	MPI_Type_contiguous(dim, MPI_INT, &vec_t);
	MPI_Type_commit(&vec_t); 

	int extra = 0;
	allocateMatrix(&mat, dim, &matdata, dim);
    	if(world_rank == 0) {
    		extra = dim - p*world_size;
    		allocateMatrix(&tam, p + extra, &tamdata, dim);
		sendbufp = &( mat[ extra ][ 0 ] );
    	} else {
    		allocateMatrix(&tam, p, &tamdata, dim);
    	}
	
	
    MPI_Barrier(MPI_COMM_WORLD);
    
    #pragma omp parallel shared(mat, tam, iter, vec_t, sendbufp), default(none), firstprivate(p, extra, world_rank, dim) if(nthreads > 1)
    for(int i = 0; i < iter; ++i) { 
    	
    	#pragma omp barrier
    	#pragma omp master
    	MPI_Bcast(&(mat[0][0]), dim, vec_t, 0, MPI_COMM_WORLD);
    	#pragma omp barrier
	    	
		#pragma omp for nowait collapse(2) 
    	for(int i = 0; i < p + extra; ++i) {
        	for(int j = 0; j < dim; ++j) {
   					int sx = p*world_rank + i;
   					Cell* neighbor = chooseNeighbor(sx, j, dim, mat);
            		transition(mat[sx][j], *neighbor, tam[i][j]);
        	}
    	}

    	#pragma omp barrier
    	#pragma omp master
    	MPI_Gather(&(tam[extra][0]), p, vec_t, sendbufp, p, vec_t, 0, MPI_COMM_WORLD);
    }

    
	freeMatrix(mat, matdata);
    freeMatrix(tam, tamdata);

    if(world_rank == 0) {
    	double end = MPI_Wtime();
	    printf("Dimension: %d Iterations: %d MPI processes: %d OpenMP threads: %d execution time: %f\n", 
	    	dim, iter, world_size, nthreads, end-start);
    }    
    
    MPI_Finalize();
	return 0;
}
