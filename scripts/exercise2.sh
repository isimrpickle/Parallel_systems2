#!/bin/bash

#Writing into the csv file the Execution time for a given size of matrix with different processes.

echo -e "Enter the size of matrix you want:"
read size_of_matrix

output_file="parallel_execution_times.csv"
echo "size_of_matrix,Num_Processes,Execution_Time" > $output_file # Initializing the CSV format

for num_of_processes in 2 4 5 10; do
    # Run the MPI program and capture the execution time (filter out unnecessary lines)
    Execution_Time=$(mpiexec -n $num_of_processes /home/users/sdi2000233/Parallel_systems2/modules/exercise2 $size_of_matrix | tail -n 1)

    # Append the results to the CSV file
    echo "$size_of_matrix,$num_of_processes,$Execution_Time" >> $output_file
done
