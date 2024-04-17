# Define the C++ compiler to use
CC = g++

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES = -I./headers

# Define the source file(s)
SRCS = main.cpp

# Define the output binary 
TARGET = main

# The build target executable:
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)
