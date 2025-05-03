# Compiladores
CXX = g++
CC = cc

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -Iinclude/path_finding
CFLAGS = -Wall
NO_WARN_FLAGS = -w  # Desativa todos os warnings

# Pastas
INCLUDE_DIR = include
SRC_DIR = src
AUX_DIR = $(SRC_DIR)/aux
BIN_DIR = bin
OBJ_DIR = obj

# Arquivos fonte C++
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/graph.cpp \
       $(SRC_DIR)/path_finding/dfs.cpp \
	   $(SRC_DIR)/path_finding/bfs.cpp \
	   $(SRC_DIR)/path_finding/fattest_path.cpp \
       $(SRC_DIR)/ford_fulkerson.cpp \

# Fonte e objeto em C
C_SOURCE = $(AUX_DIR)/new_washington.c
C_OBJECT = $(OBJ_DIR)/new_washington.o

# Executáveis
TARGET = $(BIN_DIR)/main
EXEC_GEN = $(BIN_DIR)/gengraph

# Alvo padrão
all: $(TARGET) $(EXEC_GEN)

# Diretórios
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilação do programa principal (C++)
$(TARGET): $(SRCS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete. Execute with ./bin/main"

# Compilação do new_washington.c (C) sem warnings
$(C_OBJECT): $(C_SOURCE) | $(OBJ_DIR)
	$(CC) $(NO_WARN_FLAGS) -c $< -o $@

# Geração do executável gengraph
$(EXEC_GEN): $(C_OBJECT) | $(BIN_DIR)
	$(CC) -o $@ $^

# Limpeza
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean
