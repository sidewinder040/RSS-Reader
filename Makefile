# Makefile for rss-reader

# Compiler and flags
CXX := clang++
CXXFLAGS := -Wall -ggdb -Wextra -std=c++20
LIBS := fmt libcurl tinyxml2
LDFLAGS := `pkg-config --libs --cflags $(LIBS)`
CXXFLAGS += $(LDFLAGS)

# Target and source files
TARGET := rss-reader
SRC := feed.cpp feed-item.cpp rss-reader.cpp main.cpp

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)
	rm -f *.o
