#include "ford_fulkerson.hpp"

int getExpectedIterations(AugPathFinder augPathFind, int maxFlow, int numVertices, int numEdges) {
    int expectedItr;

    // Plain Ford-Fulkerson
    if (augPathFind == dfs) {
        expectedItr = maxFlow; // C = maxFlow

    // Edmons-Karp
    } else if (augPathFind == bfs) {
        expectedItr = numVertices * numEdges; // O(nm)

    // Fattest Path
    } else if (augPathFind == fattestPath) {
        expectedItr = numEdges * log2(maxFlow); // O(m log C)

    } else {
        throw invalid_argument("Unknown augmentation path finding strategy");
    }

    return expectedItr;
}

void printPath(const vector<Edge*>& path, int pathFlow) {
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i]->from;
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";

    cout << ", Flow: " << pathFlow << "\n";
}

int fordFulkerson(Graph& g, 
                  AugPathFinder augPathFind) { 
    auto start = high_resolution_clock::now();

    vector<Edge*> path;
    vector<bool> visited;
    int numVertices = g.getNumVertices();
    int numEdges = g.getNumEdges();
    int maxFlow = 0;

    int numIterations = 0;
    while (true) {
        numIterations++;

        visited.assign(numVertices, false);

        path.clear();

        if (!augPathFind(g, g.source, g.sink, visited, path)) break;

        int pathFlow = INF;
        for (Edge* e : path) {
            pathFlow = min(pathFlow, e->residualCapacity()); // bottleneck
        }

        for (Edge* e : path) {
            e->augment(pathFlow);
        }

        maxFlow += pathFlow;

        vector<int> pathVertices;
        pathVertices.push_back(g.source);
        for (Edge* e : path) {
            pathVertices.push_back(e->to);
        }
    }

    // Calculate the expected number of iterations based on the algorithm variant
    int expectedIterations = getExpectedIterations(augPathFind, maxFlow, numVertices, numEdges);

    // Calculate the ratio r = I / I_bar
    double ratio = static_cast<double>(numIterations) / expectedIterations;
    cout << "Razão de iterações (I / Ī): " << ratio << "\n";

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Tempo de execução: " << duration << " ms\n";

    return maxFlow;
}



