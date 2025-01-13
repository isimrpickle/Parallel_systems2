import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

# Using 'Agg' because we will save the diagram in a PNG file
matplotlib.use('Agg')

# Loading data from the CSV file
df = pd.read_csv("parallel_execution_times.csv")

# Filter data for size_of_matrix = 100
subset = df[df["size_of_matrix"] == 100]

# Plotting the data
plt.figure(figsize=(10, 6))  # Set the figure size
plt.plot(
    subset["Num_Processes"], 
    subset["Execution_Time"], 
    marker="o", 
    label="Parallel Algorithm"
)

# Adding labels, title, and legend
plt.xlabel("Number of Processes")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution time VS Processes")
plt.grid(True)
plt.legend()

# Saving the figure to a PNG file
plt.savefig("MPI.png")



# Adding labels, title, and legend
#