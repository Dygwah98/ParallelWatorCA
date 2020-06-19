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
	static int jmap[3][2] = {{8,15}, {3,5}, {2,7}};

	ret.j = (cell.age == jmap[ret.i][1]) ? 2 : (cell.age > jmap[ret.i][0]) ? 1 : 0;

	return ret;
}

void chooseNeighbor(int pi, int pj, int& i, int& j, const int dim) {

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

void printInfo(Cell** mat, const int dim, int it) {
	
	int pop[4] = {0, 0, 0, 0};

	for(int i = 0; i < dim; ++i)
		for(int j = 0; j < dim; ++j)
			++pop[ mat[i][j].id ];
	
	printf("\n");
	printf("Iteration: %d ", it);
	printf("Sharks: %d Fishes: %d Shrimps: %d\n", pop[3], pop[2], pop[1]);
	printf("\n");
}

void runWator(Cell*** mat, Cell*** tam, const int& dim, const int& iter, Cell **ghostcells) {

	int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int partition = getPartitionSize(dim, world_size);

	int x, y;
	for(int k = 0; k < iter; ++k) {

//		printInfo(*mat, dim, k);

    	for(int i = 0; i < dim; ++i) {
        	for(int j = 0; j < dim; ++j) {

//				printf("iteration %d index %d %d\n", it, i, j);

            	if((*mat)[i][j].id != 0) {
                	chooseNeighbor(i, j, x, y, dim);
                	transition((*mat)[i][j], (*mat)[x][y], (*tam)[i][j]);
            	}
        	}
    	}

    	std::swap(mat, tam);

    	if(world_rank == 0) {
    		for(int i = 0; i < world_size; ++i)
    			updateGhostCells(ghostcells, partition, *mat, dim, i);
    	}
    }
}

int getPartitionSize(const int dim, int world_size) {

	int ret = dim/2;
	while(ret > 1) {
		if(dim % ret == 0 && (dim/ret)*(dim/ret) > world_size)
			break;
		--ret;
	}

	return ret;
}

void updateGhostCells(Cell **ghostcells, const int partition, Cell **mat, const int dim, const int world_rank) {

	int temp = (4*partition + 4);
	int sx = ((world_rank/(dim/partition)) * partition -1 + dim) % dim;
	int sy = ((world_rank%(dim/partition)) * partition -1 + dim) % dim;
	int fx = (sx + partition) % dim;
	int fy = (sy + partition) % dim; 

	int s = world_rank * temp;
	int ds = partition + 1;
	for(int i = -1; i <= partition; ++i)
	(*ghostcells)[s + 1 + i] = mat[sx][(sy + i + dim) % dim];
	
	for(int i = 0; i <= partition; ++i)
	(*ghostcells)[s + ds + i] = mat[(sx + i) % dim][fy];
	
	for(int i = 0; i <= partition; ++i)
	(*ghostcells)[s + 2*ds + i] = mat[fx][(fy - i + dim) % dim];

	for(int i = 0; i < partition; ++i)
	(*ghostcells)[s + 3*ds + i] = mat[(fx - i + dim) % dim][sy];
}

void allocateGhostCells(Cell **ghostcells, const int partition, Cell **mat, const int dim, const int world_size) {

	int temp = (4*partition + 4) * world_size;
	(*ghostcells) = new Cell[temp];

	for(int i = 0; i < world_size; ++i)
		updateGhostCells(ghostcells, partition, mat, dim, i);
}