# Compiladores
CXX = g++
CC = cc

# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -Iinclude/path_finding
CFLAGS = -Wall
NO_WARN_FLAGS = -w

# Diretórios
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
AUX_DIR = $(SRC_DIR)/aux

# Arquivos C++
SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(SRC_DIR)/path_finding/*.cpp)

REF_SRC = $(SRC_DIR)/aux/maxflow.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp

# Arquivo C
C_SOURCE = $(AUX_DIR)/new_washington.c
C_OBJECT = $(OBJ_DIR)/new_washington.o

# Executáveis
MAIN_EXE = $(BIN_DIR)/main
REF_EXE = $(BIN_DIR)/maxflow
GENGRAPH_EXE = $(BIN_DIR)/gengraph

# Alvo padrão
all: $(MAIN_EXE) $(REF_EXE) $(GENGRAPH_EXE)

# Criar diretórios
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Compila executável principal
$(MAIN_EXE): $(filter-out $(REF_SRC), $(SRCS)) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Compilado: ./bin/main"

# Compila executável de teste
$(REF_EXE): $(REF_SRC) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✅ Compilado: ./bin/maxflow"

# Compila new_washington.c
$(C_OBJECT): $(C_SOURCE) | $(OBJ_DIR)
	$(CC) $(NO_WARN_FLAGS) -c $< -o $@

# Compila gengraph
$(GENGRAPH_EXE): $(C_OBJECT) | $(BIN_DIR)
	$(CC) -o $@ $^

# Limpeza
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean
