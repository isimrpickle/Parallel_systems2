#!/bin/bash

echo -e "Enter the size of matrix you want:"
read size_of_matrix

echo -e "Enter the number of births you want:"
read num_births

output_file="Game_of_Life_execution_times.csv"
echo "size_of_matrix,Num_Processes,Num_births,Execution_Time" > $output_file # Initializing the CSV format

for num_of_processes in 2 4 8; do
    # Run the MPI program and capture the execution time (filter out unnecessary lines)
    Execution_Time=$(mpiexec -n $num_of_processes /home/users/sdi2000233/Parallel_systems2/modules/Game_of_Life $size_of_matrix $num_births | tail -n 1)

    # Append the results to the CSV file
    echo "$size_of_matrix,$num_of_processes,$num_births,$Execution_Time" >> $output_file
done
