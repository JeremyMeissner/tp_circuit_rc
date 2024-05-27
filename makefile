# Define the C compiler
CC = gcc

# Define the target executable
TARGET = circuits

# Define the source file
SRC = circuits.c

# Define the Python script
PYTHON_SCRIPT = display.py

# Default target to compile and runs
all: $(TARGET) run_python

# Compile the C program
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

# Run the Python script
run_python:
	./circuits
	python3 $(PYTHON_SCRIPT)

# Clean target to remove the compiled executable
clean:
	rm -f $(TARGET)
