#
# Basic makefile for consistant building
#

# executable name
TARGET = shell

# compiler: gcc for C, g++ for C++
CC = g++

# compilter flags:
# -g     adds debugging information to the executable, enableing debugging with gdb
# -Wall  turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET)

clean:
	$(RM) $(TARGET)
