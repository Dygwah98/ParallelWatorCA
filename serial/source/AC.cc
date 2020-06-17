#include"../headers/AC.h"

CellKey calculateCellKey(const Cell& cell) {

	CellKey ret;
	ret.i = cell.id - 1;
	if(cell.id == 1) {

		ret.j = (cell.age == 15) ? 2 : (cell.age%13)/8;

	} else if(cell.id == 2) {

		ret.j = (cell.age == 5) ? 2 : cell.age/3;

	} else if(cell.id == 3) {

		ret.j = (cell.age == 7) ? 2 : (cell.age > 1) ? 1 : 0;

	} else {

		ret.j = 0;
	}

	return ret;
}

void chooseNeigbor(int pi, int pj, int& i, int& j, Cell** mat, const int dim) {

//	printf("starting chooseNeigbor(%d,%d,%d,%d,%d...\n", pi, pj,i,j, mat);

	int posi = rand()%3;
	int posj = rand()%3;
	if(posi == 1 && posj == 1) {
		posi = posj = 0;
	}
	int si = (pi-1 + dim) % dim;
	int sj = (pj-1 + dim) % dim;
	
	i = (si + posi) % dim;
	j = (sj + posj) % dim;				

//	printf("Before id check\n");

	//if a shrimp
	if(mat[pi][pj].id == 1) {
		
//		printf("First id check, i: %d j: %d\n", i, j);

		if(mat[i][j].id != 0)
		for(int ind = 0; ind < 3; ++ind) {
//			printf("       posi %d posj %d\n", posi, posj);
			for(int ind2 = 0; ind2 < 3; ++ind2) {
				posj = (posj + 1) % 3;
				if(mat[(si + posi) % dim][(sj + posj) % dim].id == 0 && posi != 1 && posj != 1) {
					i = (si + posi) % dim;
					j = (sj + posj) % dim;
//					printf("Returning %d %d at %d %d\n", i, j, ind, ind2);
					return;
				}
			}
			posi = (posi + 1) % 3;
			if(posi == 0)
				posj = 0;
		}
	//if a fish
	} else if(mat[pi][pj].id == 2) {

//		printf("Second id check, i: %d j: %d\n", i, j);

		if(mat[i][j].id == 3)
		for(int ind = 0; ind < 3; ++ind) {
			for(int ind2 = 0; ind2 < 3; ++ind2) {
				posj = (posj + 1) % 3;
				if(mat[(si + posi) % dim][(sj + posj) % dim].id == 0 && posi != 1 && posj != 1) {
					i = (si + posi) % dim;
					j = (sj + posj) % dim;
//					printf("Returning %d %d at %d %d\n", i, j, ind, ind2);
					return;
				}
			}
			posi = (posi + 1) % 3;
		}
	}

//	printf("Returning %d %d at end\n", i, j);
}

void transition(Cell& cell, Cell& neighbor, Cell& newcell) {

	//printf("starting transition({%d},{%d}...\n", cell.id, neighbor.id);

	CellKey key1 = calculateCellKey(cell);
	CellKey key2 = calculateCellKey(neighbor);

	int i = key[key1.i][key1.j];
	int j = key[key2.i][key2.j];

	newcell.id = value_original[i][j];
	newcell.age = (key1.j == 2) ? 0 : cell.age + 1;
}

void printMatrix(Cell** mat, const int dim) {

	int pop[4] = {0, 0, 0, 0};

	for(int i = 0; i < dim; ++i) {
		for(int j = 0; j < dim; ++j) {
			printf("%d ", mat[i][j].id);
			++pop[mat[i][j].id];
		}
		printf("\n");
	}
	printf("\n");
	printf("Sharks: %d\nFishes: %d\nShrimps: %d\n", pop[3], pop[2], pop[1]);
	printf("\n");
}