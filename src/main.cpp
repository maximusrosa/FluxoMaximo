#include "utils.hpp"

int main(int argc, char *argv[]) {
    string filePath, methodName;
    AugPathFinder pathFinder;

    parseArguments(argc, argv, filePath, pathFinder, methodName);

    ifstream file(filePath);
    if (!file) return 1;

    Graph g(file);
    string graphType = getGraphTypeFromPath(filePath);
    int numVertices = g.getNumVertices();
    int numEdges = g.getNumEdges();

    GraphInfo graphInfo = {graphType, numVertices, numEdges};

    FFstats stats = fordFulkerson(g, pathFinder);
    //stats.print();
    
    string outputFile = "results-" + methodName + ".csv";
    saveStatsToCSV(outputFile, graphInfo, stats);

    return 0;
}
