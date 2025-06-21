# Compiler and compiler flags
CC = gcc
# Added -D_WIN32 to CFLAGS to force the compiler to recognize the Windows environment
CFLAGS = -Wall -Wextra -std=c11 -O2 -I. -D_WIN32

# Source files
SRCS = main.c sensor_simulator.c complementary.c logger.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = sensor_fusion_sim

# Default target: build all
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET) log.csv

# Phony targets
.PHONY: all clean
