#!/bin/bash

# Caminhos dos executáveis
MAIN_EXE=./bin/main
REF_EXE=./bin/maxflow

# Métodos de busca a testar
METHODS=("fattest")

# Lista de pastas a serem percorridas
FOLDERS=( "random_level" "basic_line")

# Loop por todos os métodos de busca
for method in "${METHODS[@]}"; do
    # Loop por todas as pastas especificadas
    for folder in "${FOLDERS[@]}"; do
        # Loop por todos os arquivos .dimacs dentro da pasta atual, limitando a 30 arquivos por diretório
        for graph in $(find "graphs/$folder" -name "*.dimacs" -printf "%T@ %p\n" | sort -n | cut -f2- -d" " | awk -F/ '{count[$3]++; if (count[$3] <= 24) print $0}' | tail -n +1); do
            echo "======================================================="
            echo "Rodando: $graph ($method)"
            echo "======================================================="

            # Roda seu algoritmo e mostra toda a saída
            echo "--- Executando... ---"
            $MAIN_EXE "$graph" "$method"
            echo "--- Fim de execução ---"

            # (Opcional) Rodar algoritmo de referência para comparar
            # echo "--- Saída do algoritmo de referência ---"
            # $REF_EXE < "$graph"
            # echo "---------------------------------------"

            echo ""
        done
    done
done

echo "Todas as execuções concluídas."
