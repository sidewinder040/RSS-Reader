# Makefile for rss-reader

# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -ggdb -Wextra -pedantic -std=c++20 $(shell pkg-config --cflags fmt libcurl tinyxml2)
LDFLAGS = $(shell pkg-config --libs fmt libcurl tinyxml2)

# Target and source files
TARGET = rss-reader
SRCS = feed.cpp feed-item.cpp rss-reader.cpp main.cpp tinyxml2.cpp
OBJS = $(SRCS:.cpp=.o)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
# Clean target
clean:
	rm -f $(OBJS) $(TARGET)
