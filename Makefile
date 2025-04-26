# Makefile for rss-reader

# Compiler and flags
CXX := clang++
CXXFLAGS := -Wall -ggdb -Wextra -std=c++17

# Target and source files
TARGET := rss-reader
SRC := rss-reader.cpp main.cpp

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)