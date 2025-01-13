#!/bin/bash

echo -e "Enter the size of matrix you want:"
read size_of_matrix

output_file="serial_execution_times.csv"
echo "size_of_matrix,Execution_Time" > $output_file # Initializing the CSV format

for num_of_processes in 2 4 8; do
    # Run the MPI program and capture the execution time (filter out unnecessary lines)
    Execution_Time=$(/home/users/sdi2000233/Parallel_systems2/modules/exercise2 $size_of_matrix | tail -n 1)

    # Append the results to the CSV file
    echo "$size_of_matrix,$Execution_Time" >> $output_file
done
