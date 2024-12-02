# Compiler
CC = gcc

# Output executable
OUTPUT = game.exe

# Source files
SRC = main.c

# Libraries to link
LIBS = -lraylib -ljson-c -lopengl32 -lgdi32 -lwinmm 

# Compiler flags
CFLAGS = -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) $(LIBS)

# Default target
all: $(OUTPUT)

# Build the executable
$(OUTPUT): $(SRC)
	$(CC) $(SRC) -o $(OUTPUT) $(CFLAGS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(OUTPUT)


