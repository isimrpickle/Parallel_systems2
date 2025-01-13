#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <my_rand.h>
#include <time.h>
#include <timer.h>
/*Γράψτε ένα πρόγραμμα MPI που να υπολογίζει τον πολλαπλασιασμό πίνακα-διανύσματος χρησιμοποιώντας κατανομή
του πίνακα κατά μπλοκ-στήλες. Θεωρήστε ότι η διεργασία 0 δημιουργεί τον πίνακα nxn και το διάνυσμα, και στέλνει
μόνο τα απαραίτητα δεδομένα στις υπόλοιπες διεργασίες για να πραγματοποιηθεί ο παράλληλος υπολογισμός. Το
πρόγραμμά σας θα πρέπει να δέχεται σαν όρισμα το μέγεθος του πίνακα n. Θεωρήστε ότι ο πίνακας είναι τετράγωνος,
τάξης n, με το n να δίνεται σαν όρισμα γραμμής εντολής κατά την εκτέλεση του προγράμματος και να διαιρείται
ακριβώς από το comm_sz. Αξιολογήστε την απόδοση του παράλληλου προγράμματος σας για διαφορετικό αριθμό
κόμβων και αντίστοιχο μέγεθος πίνακα τάξης n σε σχέση με τον σειριακό αλγόριθμο. Παρατηρείτε επιτάχυνση και γιατί;*/


void vectorXmatrix(int *local_matrix, int *local_result, int *vector, int rows_per_process, int size_of_matrix) {
    for (int row = 0; row < rows_per_process; row++) {
        int result = 0;
        for (int column = 0; column < size_of_matrix; column++) {
            result += local_matrix[row * size_of_matrix + column] * vector[column];
        }
        local_result[row] = result;
    }
}




int main(int argc,char**argv){
    int comm_sz;
    int my_rank;

    int size_of_matrix = 100;
    double before;
    GET_TIME(before);
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    srand(time(0));
    int *vector = malloc(sizeof(int) * size_of_matrix);
    int* matrix; 
    int* result;

    if(my_rank==0){
        printf("Initial matrix\n");
        //Initializing matrix 
        matrix = malloc(size_of_matrix *size_of_matrix* sizeof(int));
        result = malloc(size_of_matrix *sizeof(int)); //the final result will be printed here
        for(int row=0;row<size_of_matrix;row++){
            for (int collumn=0;collumn<size_of_matrix;collumn++){
                matrix[row*size_of_matrix+collumn] = rand()%10;
                printf("[%d]",matrix[row*size_of_matrix+collumn]);
            }
            printf("\n");
            vector[row] = rand()%10; 

        }

    }       
    if(my_rank==0){
        printf("the vector is \n");
        for(int i = 0; i < size_of_matrix; i++){
            printf("[%d]",vector[i]);
        }
        printf("\n");
    }

    MPI_Bcast(vector,size_of_matrix,MPI_INT,0,MPI_COMM_WORLD); //even though process 0 initializes it is needed by every other process so the multiplication can happen.
    int sendcount = size_of_matrix*size_of_matrix/comm_sz;
    int rows_per_process = size_of_matrix/comm_sz;
    int* local_result = malloc(rows_per_process * sizeof(int)); // Initializing result vector for each process
    int* local_matrix = malloc(rows_per_process*size_of_matrix * sizeof(int));

    //sharing the inital matrix and vector trough the processes.
    MPI_Scatter(matrix,sendcount,MPI_INT,local_matrix,sendcount,MPI_INT,0,MPI_COMM_WORLD);

    vectorXmatrix(local_matrix,local_result,vector,rows_per_process,size_of_matrix);

    MPI_Gather(local_result,rows_per_process,MPI_INT,result,rows_per_process,MPI_INT,0,MPI_COMM_WORLD);

    if(my_rank==0){
        printf("\nResult:\n");
        for(int i=0; i<size_of_matrix;i++){
            printf("[%d]\n",result[i]);
        }
        free(matrix);
        free(result);
        
    }


    free(vector);
    free(local_matrix);
    free(local_result);
    MPI_Finalize();
    double after;
    GET_TIME(after);
    double elapsed = after - before;
    printf("\n%f",elapsed);    
}