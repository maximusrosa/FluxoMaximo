#include "path_finding/fattest_path.hpp"

bool State::operator<(const State& other) const {
    return bottleneck < other.bottleneck;
}

bool fattestPath(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path, PathSearchStats& stats) {
    int n = g.getNumVertices();
    vector<Edge*> parent(n, nullptr);
    vector<int> bottleneck(n, 0);
    vector<bool> inQueue(n, false); // Track which nodes are in the queue

    priority_queue<State> pq;
    bottleneck[source] = INF;
    pq.push({source, bottleneck[source]});
    visited[source] = true;
    inQueue[source] = true; // Mark source as in queue

    // Estatísticas
    int insertions = 1;    // Initial insertion of source
    int deletemins = 0;
    int updates = 0;       // Track updates separately

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        deletemins++;
        
        int u = curr.node;
        inQueue[u] = false; // Node is no longer in queue
        
        if (curr.bottleneck < bottleneck[u]) {
            // Skip outdated entries in the priority queue
            continue;
        }
        
        if (u == sink) {
            // Reconstruct path
            int v = sink;
            while (v != source) {
                Edge* e = parent[v];
                path.push_back(e);
                v = e->from;
            }
            reverse(path.begin(), path.end());
            
            // Acumulate stats before returning success
            stats.i_bar += static_cast<double>(insertions) / g.getNumVertices();
            stats.d_bar += static_cast<double>(deletemins) / g.getNumVertices();
            stats.u_bar += static_cast<double>(updates) / g.getNumEdges();
            
            return true;
        }
        
        for (Edge* e : g.getAdjList(u)) {
            if (e->residualCapacity() <= 0) continue;
            
            int v = e->to;
            int newBottleneck = min(bottleneck[u], e->residualCapacity());
            
            if (newBottleneck > bottleneck[v]) {
                bottleneck[v] = newBottleneck;
                parent[v] = e;
                
                // Check if this is a new insertion or an update
                if (!inQueue[v]) {
                    // New insertion
                    pq.push({v, newBottleneck});
                    inQueue[v] = true;
                    insertions++;
                } else {
                    // Update (we need to reinsert as priority queues don't support direct updates)
                    pq.push({v, newBottleneck});
                    updates++;
                }
            }
        }
    }

    // Se falhou, ainda assim acumula stats
    stats.i_bar += static_cast<double>(insertions) / g.getNumVertices();
    stats.d_bar += static_cast<double>(deletemins) / g.getNumVertices();
    stats.u_bar += static_cast<double>(updates) / g.getNumEdges();
    
    return false;
}