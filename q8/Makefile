# Makefile for q8
# Usage:
#   make

OPT := -O2
CXX = g++
CXXFLAGS = -std=c++11 -Wall ${OPT}

TARGET = q8
SRCS = q8.cc UnionFind.cc
OBJS = $(SRCS:.cc=.o)
HEADERS = Point.h q8.h UnionFind.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
