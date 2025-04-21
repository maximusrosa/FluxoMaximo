INCLUDE_DIR = include
SRC_DIR = src

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/graph.cpp $(SRC_DIR)/ford_fulkerson.cpp
TARGET = bin/main

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(INCLUDE_DIR)

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete. Run the program with ./bin/main"
clean:
	rm -rf bin

.PHONY: all clean
