# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Executable name
TARGET = bank_simulator

# Source files
SRC = main.c bank.c

# Object files
OBJ = $(SRC:.c=.o)

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJ) $(TARGET)

# Run program directly
run: all
	./$(TARGET)
