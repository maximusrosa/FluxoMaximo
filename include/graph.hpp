#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int capacity;
    int flow;
    Edge* residual;

    Edge(int to, int capacity);

    int residualCapacity() const;
    void augment(int bottleneck);
};

class Graph {
private:
    int numVertices;
    int numEdges;
    vector<vector<Edge*>> adjVector;

public:
    Graph(int numVertices);
    Graph(istream& in);

    ~Graph();

    int getNumVertices() const;
    int getNumEdges() const;
    const vector<Edge*>& getAdjList(int u) const;

    void addEdge(int u, int v, int capacity);
};
