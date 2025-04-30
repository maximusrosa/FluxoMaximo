#include "graph.hpp"
#include "fattest_path.hpp"

bool State::operator<(const State& other) const {
    return bottleneck < other.bottleneck; // max-heap (prioriza maior bottleneck)
}

bool fattestPath(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path) {
    int n = g.getNumVertices();
    vector<Edge*> parent(n, nullptr);
    vector<int> bottleneck(n, 0);

    priority_queue<State> pq;
    bottleneck[source] = INF;
    pq.push({source, bottleneck[source]});
    visited[source] = true;

    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();

        if (u == sink) {
            // Reconstrói o caminho a partir do nó de destino
            while (parent[u] != nullptr) {
                path.push_back(parent[u]);
                u = parent[u]->residual->to;
            }
            reverse(path.begin(), path.end());
            return true;
        }

        // Verifica se existe pseudocaminho aumentante
        for (Edge* e : g.getAdjList(u)) {
            int v = e->to;

            if (!visited[v] && e->residualCapacity() > 0) {
                int newBottleneck = min(bottleneck[u], e->residualCapacity());

                if (newBottleneck > bottleneck[v]) {
                    bottleneck[v] = newBottleneck;
                    parent[v] = e;
                    pq.push({v, bottleneck[v]});
                }
            }
        }
    }

    return false;
}
