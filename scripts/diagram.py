import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

#Using 'Agg' because we will save the diagram in a PNG file
matplotlib.use('Agg')

# Loading data from the CSV file
df = pd.read_csv("parallel_execution_times.csv")

# Filter data for size_of_matrix = 100
subset = df[df["size_of_matrix"] == 64]

# Plotting the data
plt.figure(figsize=(10, 6))  # Set the figure size
plt.plot(
    subset["Num_Processes"], 
    subset["Execution_Time"], 
    marker="o", 
    label="Game_of_Life"
)

# Adding labels, title, and legend
plt.xlabel("Number of Processes")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution time VS Processes")
plt.grid(True)
plt.legend()

# Saving the figure to a PNG file
plt.savefig("Game_of_Life.png")

# import pandas as pd
# import matplotlib.pyplot as plt
# import matplotlib

# # Using 'Agg' because we will save the diagram in a PNG file
# matplotlib.use('Agg')

# # Loading data from the CSV file
# df = pd.read_csv("serial_execution_times.csv")

# # Filter data for size_of_matrix = 100
# summary = df.groupby(["size_of_matrix"])["Execution_Time"].mean().reset_index()

# plt.figure(figsize=(10, 6))
# plt.plot(summary["size_of_matrix"], summary["Execution_Time"], marker='o', label="Serial Algorithm")

# # Adding labels, title, and legend
# plt.xlabel("Matrix Size")
# plt.ylabel("Mean Execution Time (seconds)")
# plt.title("Execution Time for Serial Algorithm")
# plt.grid()
# plt.legend()

# # Saving the plot as a PNG file
# plt.savefig("Serial.png")
