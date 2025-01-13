#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_rand.h"
#include "timer.h"
#include <mpi.h>
#include <string.h>
/* Εάν ένας οργανισμός (κατειλημμένη θέση) έχει λιγότερους από 2 γειτονικούς οργανισμούς, ο οργανισμός
πεθαίνει από μοναξιά.
 Εάν ένας οργανισμός έχει 2 ή 3 γειτονικούς οργανισμούς, ο οργανισμός επιζεί στην επόμενη γενιά.
 Εάν ένας οργανισμός έχει περισσότερους από 3 γειτονικούς οργανισμούς, ο οργανισμός πεθαίνει λόγω
υπερπληθυσμού.
 Εάν μία μη κατειλημμένη θέση έχει ακριβώς 3 γειτονικούς οργανισμούς, αυτή η θέση θα καταληφθεί στην
επόμενη γενιά από έναν νέο οργανισμό, δηλαδή ένας οργανισμός γεννιέται.*/

int size_of_grid = 64;


void updating_grid(int* local_matrix,int rows_per_process,const int* below_rcv_buff,const int* above_rcv_buff){
    int* temp_matrix = malloc(rows_per_process * size_of_grid * sizeof(int));
    /*  
    the grid will be shared between the processes so for the first row of each process(minus the first one) and the last row
    an exchange of rows will be needed(the row before the 1st row of the current process and the row after the last row of the current process)

    
    */
    for(int row=0;row<rows_per_process;row++){

        for(int collumn = 0; collumn < size_of_grid;collumn++){
            int counter_if_Is=0;
            int curr_state = local_matrix[row * size_of_grid + collumn];

            for(int checking_row = row-1; checking_row<=row+1;checking_row++){
                for(int checking_collumn = collumn-1;checking_collumn<=collumn+1;checking_collumn++){
                    if((checking_row>=0 && checking_row<rows_per_process) && (checking_collumn>=0 && checking_collumn<size_of_grid)){
                        if(checking_row== row &&checking_collumn==collumn){ //skip the current state
                            continue;
                        }
                        if(local_matrix[checking_row*size_of_grid+checking_collumn]==1)
                            counter_if_Is++;
                    }

                     // Handling the above boundary for each process
                    else if(checking_row == -1 && above_rcv_buff != NULL) {
                        if (checking_collumn >= 0 && checking_collumn < size_of_grid) {
                            if (above_rcv_buff[checking_collumn] == 1) {
                                counter_if_Is++;
                            }
                        }
                    }

                    // Handling the bottom boundary for each process
                    else if(checking_row == size_of_grid && below_rcv_buff != NULL) {
                        if (checking_collumn >= 0 && checking_collumn < size_of_grid) {
                            if (below_rcv_buff[checking_collumn] == 1) {
                                counter_if_Is++;
                            }
                        }
                    }
                }
            }    

            //applying the rules!
            if(curr_state==1){ //if it's initially alive then:
                if(counter_if_Is<2 || counter_if_Is>3)
                    temp_matrix[row*size_of_grid+collumn] = 0; //assigning it as dead (loneliness)
                else
                    temp_matrix[row*size_of_grid+collumn] = 1; //staying the same(alive)
            }
            else
                if(counter_if_Is==3)
                    temp_matrix[row*size_of_grid+collumn]=1; //the state becomes alive (neighbors ==3)
                else
                    temp_matrix [row*size_of_grid+collumn]=0; //staying dead

        }
        
    }

    memcpy(local_matrix, temp_matrix, rows_per_process * size_of_grid * sizeof(int));

}


int main(int argc,char**argv){
    int comm_sz;
    int my_rank; 
    int births = 1000;
    //int size_of_grid=strtol(argv[2],NULL,10);
    int* grid = malloc(size_of_grid* size_of_grid*sizeof(int*));

    double before;
    GET_TIME(before);
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    //passing values from command line: number of births, the size of grid, 0 for serial/1 for parallel, number of threads
    if(my_rank==0){
      
            
        for(int row =0;row<size_of_grid;row++){
            for(int collumn = 0; collumn < size_of_grid;collumn++){
                    unsigned int random_seed = rand();
                    random_seed ^= (row + collumn); // XOR with (row+column) in order to make the seed vary
                    int state_of_point = (my_drand(&random_seed) > 0.5) ? 1 : 0; //if my drand returns a double >0.5 then assign it as 1 else as 0

                    grid[row*size_of_grid+collumn] = state_of_point;
            }
        }
    }
    int rows_per_process = size_of_grid / comm_sz;

    int* local_matrix = malloc(rows_per_process*size_of_grid * sizeof(int*));


   


    MPI_Scatter(grid,rows_per_process*size_of_grid/comm_sz,MPI_INT,local_matrix,rows_per_process*size_of_grid/comm_sz, MPI_INT,0,MPI_COMM_WORLD);

    int* below_rcv_buff = malloc(size_of_grid * sizeof(int)); //receiving first row from the grid after the current
    int* above_rcv_buff = malloc(size_of_grid * sizeof(int)); //receiving last row from the grid before the current one

    // double before,now;
    if(my_rank>0){
        while(births>0){
            int rank_above = (my_rank == comm_sz - 1)? MPI_PROC_NULL: my_rank + 1;
            int rank_below = (my_rank == 1) ? MPI_PROC_NULL : my_rank - 1;

            // Send first row of current local grid and receive first row
            MPI_Sendrecv(local_matrix,size_of_grid,MPI_INT,rank_below,0
            ,below_rcv_buff,size_of_grid,MPI_INT,rank_above,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            MPI_Sendrecv(&local_matrix [(rows_per_process-1)*size_of_grid],size_of_grid,MPI_INT,rank_above,1
            ,above_rcv_buff,size_of_grid,MPI_INT,rank_below,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            births--;
            updating_grid(local_matrix,rows_per_process,below_rcv_buff,above_rcv_buff);

            MPI_Gather(local_matrix,size_of_grid*size_of_grid/comm_sz,MPI_INT,grid,size_of_grid*size_of_grid/comm_sz,MPI_INT,0,MPI_COMM_WORLD);
        }
    }

    // double elapsed_time=now-before;
    // printf("%f",elapsed_time);

    if(my_rank==0){
        //deallocating the 2d array.
        free(grid);
    }
   
    free(local_matrix);
    free(below_rcv_buff);
    free(above_rcv_buff);
    MPI_Finalize();
    double after;
    GET_TIME(after);
    printf("%lf\n",after-before);
    
}