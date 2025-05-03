#include "ford_fulkerson.hpp"
#include <string>

void testeRapido(){
    Graph g(6);

    g.addEdge(0, 1, 3); // s -> v1
    g.addEdge(0, 2, 7); // s -> v2
    g.addEdge(1, 3, 3); // v1 -> v3
    g.addEdge(1, 4, 4); // v1 -> v4
    g.addEdge(2, 1, 5); // v2 -> v1
    g.addEdge(2, 4, 3); // v2 -> v4
    g.addEdge(3, 4, 3); // v3 -> v4
    g.addEdge(3, 5, 2); // v3 -> t
    g.addEdge(4, 5, 6); // v4 -> t

    g.source = 0; // s
    g.sink = 5;   // t
    int maxFlow = fordFulkerson(g, bfs); 

    cout << "The maximum possible flow is " << maxFlow << "\n";
}

void printUsage(const char* programName) {
    cerr << "Uso: " << programName << " <arquivo_de_grafo> <método_de_busca>" << endl;
    cerr << "Métodos de busca disponíveis: bfs, dfs, fattest" << endl;
}

void parseArguments(int argc, char *argv[], string& filePath, AugPathFinder& pathFinder) {
    if (argc != 3) {
        cerr << "Número inválido de argumentos." << endl;
        printUsage(argv[0]);
        exit(1);
    }

    filePath = argv[1];
    string searchMethod = argv[2];

    switch (searchMethod[0]) {
        case 'b':
            cout << "Usando método de busca BFS" << endl;
            pathFinder = bfs;
            break;

        case 'd':
            cout << "Usando método de busca DFS" << endl;
            pathFinder = dfs;
            break;

        case 'f':
            cout << "Usando método de busca Fattest Path" << endl;
            pathFinder = fattestPath;
            break;

        default:
            cerr << "Método de busca inválido: " << searchMethod << endl;
            printUsage(argv[0]);
            exit(1);
    }

}

int main(int argc, char *argv[]) {
    string filePath;
    AugPathFinder pathFinder;

    parseArguments(argc, argv, filePath, pathFinder);

    ifstream in(filePath);
    cout << "Lendo grafo do arquivo: " << filePath << endl;
    if (!in) {
        cerr << "Erro ao abrir o arquivo: " << filePath << endl;
        return 1;
    }

    Graph g(in);
    int maxFlow = fordFulkerson(g, pathFinder); 

    cout << "O fluxo máximo possível é " << maxFlow << endl;
    return 0;
}