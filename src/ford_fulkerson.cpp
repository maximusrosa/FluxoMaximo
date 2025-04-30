#include "ford_fulkerson.hpp"

int fordFulkerson(Graph& g, 
                  AugPathFinder augPathFind) { 
    int maxFlow = 0;
    vector<Edge*> path;
    vector<bool> visited;

    
    while (true) {
        visited.assign(g.getNumVertices(), false);
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

        cout << "Path: ";
        for (size_t i = 0; i < pathVertices.size(); ++i) {
            cout << pathVertices[i];
            if (i < pathVertices.size() - 1) cout << " -> ";
        }
        cout << ", Flow: " << pathFlow << "\n";
    }

    return maxFlow;
}
