#include "ford_fulkerson.hpp"
#include "path_finding/search_stats.hpp"

int getExpectedIterations(AugPathFinder augPathFind, int maxFlow, int numVertices, int numEdges) {
    int expectedItr;

    // Plain Ford-Fulkerson
    if (augPathFind == dfs) {
        expectedItr = maxFlow; // C = maxFlow

    // Edmons-Karp
    } else if (augPathFind == bfs) {
        expectedItr = round((numVertices * numEdges) / 2); // O(nm / 2)

    // Fattest Path
    } else if (augPathFind == fattestPath) {
        expectedItr = round(numEdges * log2(maxFlow)); // O(m log C)

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

FFstats fordFulkerson(Graph& g, 
                  AugPathFinder augPathFind) { 
    auto start = high_resolution_clock::now();

    vector<Edge*> path;
    vector<bool> visited;
    int numVertices = g.getNumVertices();
    int numEdges = g.getNumEdges();
    int maxFlow = 0;

    PathSearchStats searchStats;

    int numIterations = 0;
    while (true) {
        numIterations++;

        visited.assign(numVertices, false);

        path.clear();

        if (!augPathFind(g, g.source, g.sink, visited, path, searchStats)) break; 
    
        int pathFlow = INF;
        for (Edge* e : path) {
            pathFlow = min(pathFlow, e->residualCapacity()); // bottleneck
        }

        for (Edge* e : path) {
            e->augment(pathFlow);
        }

        maxFlow += pathFlow;
    }

    // Calcula a média das estatísticas
    if (augPathFind == fattestPath){
        searchStats.i_bar /= numIterations;
        searchStats.d_bar /= numIterations;
        searchStats.u_bar /= numIterations;
    }
    else {
        searchStats.s_bar /= numIterations;
        searchStats.t_bar /= numIterations;
    }

    // Number of iterations based on the theoretical complexity of the algorithm variant
    int expectedIterations = getExpectedIterations(augPathFind, maxFlow, numVertices, numEdges);

    double ratio = static_cast<double>(numIterations) / expectedIterations;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    return FFstats{
        maxFlow,
        ratio,
        static_cast<double>(duration),
        searchStats
    };
}



