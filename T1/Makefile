# Define the C++ compiler to use
CC = g++

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES = -I./headers

# Define the source file(s)
SRCS = ./source/main.cpp ./source/EDF.cpp ./source/RM.cpp ./source/scheduler.cpp ./source/process_control_block.cpp ./source/process.cpp ./source/CPU.cpp

# Define the output binary 
TARGET = main

# The build target executable:
all: clean $(TARGET) 

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)
