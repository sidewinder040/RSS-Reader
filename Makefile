# Makefile for rss-reader

# Compiler and flags
CXX := clang++
CXXFLAGS := -Wall -ggdb -Wextra -std=c++17
LDFLAGS := `pkg-config --libs --cflags libcurl tinyxml2`
CXXFLAGS += $(LDFLAGS)

# Target and source files
TARGET := rss-reader
SRC := feed-item.cpp rss-reader.cpp main.cpp

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)
	rm -f *.o
