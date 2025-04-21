#include "graph.hpp"

Edge::Edge(int to, int capacity) : to(to), capacity(capacity), flow(0), residual(nullptr) {}

int Edge::residualCapacity() const {
    return capacity - flow;
}

void Edge::augment(int bottleneck) {
    flow += bottleneck;
    residual->flow -= bottleneck;
}


Graph::Graph(int numVertices)
    : numVertices(numVertices), numEdges(0), adjVector(numVertices) {}

Graph::Graph(istream& in) {
    string line, dummy;
    unsigned n, m;

    while (getline(in, line) && line.substr(0, 4) != "p sp");

    stringstream linestr(line);
    linestr >> dummy >> dummy >> n >> m;

    numVertices = n;
    numEdges = m;
    adjVector.resize(n);

    for (unsigned i = 0; i < m; ++i) {
        getline(in, line);
        if (line.substr(0, 2) == "a ") {
            stringstream arc(line);
            unsigned u, v, w;
            char ac;
            arc >> ac >> u >> v >> w;
            u--; v--;
            addEdge(u, v, w);
        }
    }
}

Graph::~Graph() {
    for (auto& edges : adjVector) {
        for (Edge* e : edges) {
            delete e;
        }
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getNumEdges() const {
    return numEdges;
}

const vector<Edge*>& Graph::getAdjList(int u) const {
    return adjVector[u];
}

void Graph::addEdge(int u, int v, int capacity) {
    Edge* e1 = new Edge(v, capacity);
    Edge* e2 = new Edge(u, 0);

    e1->residual = e2;
    e2->residual = e1;

    adjVector[u].push_back(e1);
    adjVector[v].push_back(e2);

    numEdges++;
}

