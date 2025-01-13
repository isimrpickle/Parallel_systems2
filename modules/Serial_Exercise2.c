void vectorXmatrix(int *local_matrix, int *local_result, int *vector, int size_of_matrix) {
    for (int row = 0; row < size_of_matrix; row++) {
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

    int *vector = malloc(sizeof(int) * size_of_matrix);
    int* matrix = malloc(size_of_matrix*size_of_matrix *sizeof(int));
    int* result = malloc(size_of_matrix); //final result of multiplication

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

         printf("the vector is \n");
        for(int i = 0; i < size_of_matrix; i++){
            printf("[%d]",vector[i]);
        }
        printf("\n");


        vectorXmatrix(matrix,result,vector,size_of_matrix);

}