#include"AC.h"
#include<mpi.h>
#include<cassert>
#include<allegro5/allegro5.h>

int main(int argc, char const *argv[]) {

	int key[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	int value_original[10][10] = {
       //0 10 11 12 20 21 22 30 31 32
/*0*/	{0, 0, 1, 1, 0, 2, 2, 0, 3, 3},
/*10*/	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
/*11*/	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
/*12*/	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*20*/	{2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
/*21*/	{2, 2, 2, 2, 2, 0, 0, 0, 0, 0},
/*22*/	{0, 2, 2, 2, 0, 0, 0, 0, 0, 0},
/*30*/	{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
/*31*/	{3, 3, 3, 3, 3, 3, 3, 3, 0, 0},
/*32*/	{0, 3, 3, 3, 3, 3, 3, 0, 0, 0}
	};
		
	if(argc < 2) {
		fprintf(stderr, "Usage: matrix-dimension iterations-number\n");
	}

	int dim = atoi(argv[1]);
	int nthreads = atoi(argv[2]);

	int provided = 0;
	MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided);
    if(provided != MPI_THREAD_MULTIPLE) {
    	fprintf(stderr, "not enough multithread support\n");
    	MPI_Abort(MPI_COMM_WORLD,0);
    }

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	if(world_rank == 0) {
    	
    	if(!al_init()) {
    		MPI_Abort(MPI_COMM_WORLD, 0);
    	}
    }

    ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_TIMER* timer = nullptr;
	ALLEGRO_EVENT_QUEUE* queue = nullptr;
	bool redraw = true, exit = false;

	if(world_rank == 0) {

    	al_set_new_display_flags(ALLEGRO_WINDOWED);

    	display = al_create_display(dim, dim);

    	timer = al_create_timer(1/30.0f);
    	queue = al_create_event_queue();

    	al_register_event_source(queue, al_get_timer_event_source(timer));
    	al_register_event_source(queue, al_get_display_event_source(display));
    	al_pause_event_queue(queue, true);
	}

    unsigned seed = (unsigned)MPI_Wtime();

	Cell **mat = NULL;
	Cell **tam = NULL;
	Cell *matdata, *tamdata;
	Cell *sendbufp = NULL;
	
	int p = dim/world_size;

	MPI_Datatype vec_t;
	MPI_Type_contiguous(dim, MPI_INT, &vec_t);
	MPI_Type_commit(&vec_t); 

	int extra = 0;
	allocateMatrix(&mat, dim, &matdata, dim, seed);
    if(world_rank == 0) {
    	extra = dim - p*world_size;
    	allocateMatrix(&tam, p + extra, &tamdata, dim, seed);
		sendbufp = &( mat[ extra ][ 0 ] );
    } else {
    	allocateMatrix(&tam, p, &tamdata, dim, seed);
    }
		
    MPI_Barrier(MPI_COMM_WORLD);
    if(world_rank == 0)
    	printf("Allocating complete\n");

	if(world_rank == 0) {
	    al_start_timer(timer);
	    al_flush_event_queue(queue);
		al_pause_event_queue(queue, false);
	}   

	ALLEGRO_EVENT ev;

	ALLEGRO_COLOR c1 = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR c2 = al_map_rgb(200, 0, 0);
	ALLEGRO_COLOR c3 = al_map_rgb(0, 200, 0);
	ALLEGRO_COLOR c4 = al_map_rgb(0, 0, 200);
	

	int pos[8] = {-4, -3, -2, -1, 1, 2, 3, 4};
	int jmap[3][2] = {{0,7}, {3,9}, {2,7}};
			
	MPI_Request req;

	while(!exit) {
    	
    	if(world_rank == 0) {

    		if(redraw && al_is_event_queue_empty(queue)) {
    			//printf("going to print\n");
    			redraw = false;
    			
    			al_clear_to_color(al_map_rgb(0, 0, 0));	
	 			al_lock_bitmap(al_get_target_bitmap(), ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	 			al_hold_bitmap_drawing(true);
	 			for(int i = 0; i < dim; ++i)
	 			for(int j = 0; j < dim; ++j){
	 				int gid = mat[i][j]/100;
	 				switch(gid) {
	 					case 0: al_draw_pixel(i, j, c1); break;
	 					case 1: al_draw_pixel(i, j, c2); break;
	 					case 2: al_draw_pixel(i, j, c3); break;
	 					case 3: al_draw_pixel(i, j, c4); break;
	 				}
	 			}
	 			al_hold_bitmap_drawing(false);
	 			al_unlock_bitmap(al_get_target_bitmap());
	 			al_flip_display();
    			
    		} else {
    			//printf("going to wait\n");
    			do {
    				al_wait_for_event(queue, &ev);
    				if(ev.type == ALLEGRO_EVENT_TIMER) {
    					//printf("Timer event\n");
    					redraw = true;
    					break;
    				} else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    					//printf("Close event\n");
    					exit = true;
    					break;
    					}
    			} while(!al_is_event_queue_empty(queue));
    			//printf("done waiting\n");
    		}
    	}

    	MPI_Ibcast(&(mat[0][0]), dim, vec_t, 0, MPI_COMM_WORLD, &req);

	    #pragma omp parallel shared(mat, tam, vec_t, sendbufp, value_original, p, extra, world_rank, dim, pos, jmap) if(nthreads > 1)
	    {
    		int sx, cid, nid;
			int pivot, ni, nj, ti, tj;
			int chunk_size = (p + extra)/nthreads + 1;
    		unsigned seed2 = omp_get_wtime() * (omp_get_thread_num() + 1);
			
			#pragma omp for nowait schedule(guided, chunk_size) 
    		for(int i = 0; i < p + extra; ++i) {
        		sx = (p + extra)*world_rank + i;
        		for(int j = 0; j < dim; ++j) {
   					
   					pivot = pos[my_rand_r(&seed2)%8];
					ni = (sx + j/dim + pivot/3 + dim) % dim;
					nj = (j + pivot%3 + dim) % dim;

					Cell& neighbor = mat[ni][nj];
					Cell& cell = mat[sx][j];
					Cell& newcell = tam[i][j];
					
					ti = (cell/100);
					tj = (neighbor/100);
					
					cid = cell%100;
					nid = neighbor%100;
					cid = (cid == jmap[ti-1][1]) ? 2 : (cid > jmap[ti-1][0]) ? 1 : 0;
					nid = (nid == jmap[tj-1][1]) ? 2 : (nid > jmap[tj-1][0]) ? 1 : 0;

					ti = (ti == 0) ? 0 : key[ti-1][cid];
					tj = (tj == 0) ? 0 : key[tj-1][nid];

					newcell = value_original[ti][tj]*100;
					newcell += (newcell/100 == 0) ? 0 : cell%100 + 1;
        				
        			//printf("C(%d,%d):%d %d N(%d, %d):%d %d -> C(%d, %d) %d\n", sx, j, ti, cell, ni, nj, tj, neighbor, i, j, newcell);
        			
        		}
    		}
		}

    	MPI_Gather(&(tam[extra][0]), p, vec_t, sendbufp, p, vec_t, 0, MPI_COMM_WORLD);

    }
    
	freeMatrix(mat, matdata);
    freeMatrix(tam, tamdata);

    if(world_rank == 0) {

    	al_destroy_timer(timer);
    	al_destroy_event_queue(queue);
    	al_destroy_display(display);
    }    
    
    MPI_Finalize();
	return 0;
}