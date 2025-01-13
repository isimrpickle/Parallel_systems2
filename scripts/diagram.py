import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

#prints 2 diagrams 1 for the parallel algorithm and another for the serial one. If it's the row/collumn algorithm depends on the 
#subset


# Using 'Agg' because we will save the diagram in a PNG file
matplotlib.use('Agg')

# Loading data from the CSV file
df = pd.read_csv("parallel_execution_times.csv")



subset = df[df["size_of_matrix"] == 100] #0 for row algorithm,1 for collumn

summary = subset["Execution_time"].mean().reset_index()



# Adding labels, title, and legend
#