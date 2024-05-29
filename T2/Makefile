#Define the C++ compiler to use
CC = g++

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES = -I./headers

# Define the source file(s)
SRCS = $(wildcard src/*.cpp)

# Define the object file(s)
OBJS = $(SRCS:.cpp=.o)

# Define the output binary
TARGET = main

# The build target executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Rule for creating object files
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	$(RM) $(OBJS) $(TARGET)