#include "ford_fulkerson.hpp"
#include "dfs.hpp"
#include "bfs.hpp"
#include "fattest_path.hpp"

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


int main() {
    // construindo a partir do arquivo
    ifstream in("graphs/g1.gr");
    cout << "Lendo grafo do arquivo...\n";
    if (!in) {
        cerr << "Erro ao abrir o arquivo.\n";
        return 1;
    }


    Graph g(in);

    g.printGraph();

    int maxFlow = fordFulkerson(g, bfs); 

    cout << "The maximum possible flow is " << maxFlow << "\n";
    return 0;
}