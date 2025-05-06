#!/bin/bash

# Caminhos dos executáveis
MAIN_EXE=./bin/main
REF_EXE=./bin/maxflow

# Pasta com grafos (pode ser alterada para testar outra)
GRAPH_DIR="graphs/random_level"

# Métodos de busca a testar
METHODS=("dfs")

# Contador de falhas
failures=0

# Loop pelos arquivos de grafo na pasta escolhida em ordem alfabética
for graph in $(find "$GRAPH_DIR" -name "*.dimacs" -printf "%T@ %p\n" | sort -n | cut -f2- -d" "); do
    for method in "${METHODS[@]}"; do
        echo "Testando: $graph ($method)"

        # Roda seu algoritmo
        my_output=$($MAIN_EXE "$graph" "$method" | tail -n 1)

        # Roda maxflow redirecionando o grafo como entrada padrão
        ritt_output=$($REF_EXE < "$graph")

        if [ "$my_output" == "$ritt_output" ]; then
            echo "  OK → Fluxo: $my_output"
        else
            echo "  ERRO → Esperado: $ritt_output, Obtido: $my_output"
            ((failures++))
        fi
    done
done

# Relatório final
echo
if [ "$failures" -eq 0 ]; then
    echo "✅ Todos os testes passaram!"
else
    echo "❌ $failures testes falharam."
fi