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
OBJS := feed.o feed-item.o rss-reader.o main.o tinyxml2.o

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(TARGET)
	rm -f *.o
