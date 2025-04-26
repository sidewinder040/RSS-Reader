# Makefile for rss-reader

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -g -Wextra -std=c++17

# Target and source files
TARGET := rss-reader
SRC := main.cpp

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)