import matplotlib.pyplot as plt

# Read the file and store each line into a list
with open('data.txt', 'r') as file:  # Replace 'filename.txt' with your file name
    lines = [float(line.strip()) for line in file]

# Plot the values
plt.plot(lines, marker='o', linestyle='-')
plt.xlabel('Sample')
plt.ylabel('Amplitude')
plt.title('Signal processed')
plt.grid(True)
plt.show()
