#include "TSP_Greedy_Solver.h"

TSPGreedySolver::TSPGreedySolver(FullGraph *&graph) {
    graphToSolve = graph;
}

Path TSPGreedySolver::solve() {
    Path result;

    vector<Vertex*> vertexes = graphToSolve->getVertexes();
    Vertex* startVertex = vertexes.at(0);
    Vertex* currentVertex = vertexes.at(0);

    for(int i = 0; i < vertexes.size(); ++i) {
        Edge* nextEdge = findTheShortestEdge(currentVertex, result);

        if(!nextEdge)
            nextEdge = findLastEdge(startVertex, currentVertex);

        result.addEdge(nextEdge);
        selectNextVertex(currentVertex, nextEdge);
    }

    return result;
}

Edge *TSPGreedySolver::findTheShortestEdge(Vertex *vertex, Path &passedPath) {
    int minimalLength = INT32_MAX;
    Edge *resultEdge = nullptr;
    for(auto edge : vertex->getIncidentEdges()) {
        if(edge->getLength() < minimalLength && !passedPath.containsVertexes(edge->getConnectedVertexes())) {
            minimalLength = edge->getLength();
            resultEdge = edge;
        }
    }
    return resultEdge;
}

void TSPGreedySolver::selectNextVertex(Vertex *&currentVertex, Edge *edge) {
    vector<Vertex*> connectedVertexes = edge->getConnectedVertexes();
    if(currentVertex == connectedVertexes.at(0))
        currentVertex = connectedVertexes.at(1);
    else
        currentVertex = connectedVertexes.at(0);
}

Edge *TSPGreedySolver::findLastEdge(Vertex *startVertex, Vertex *currentVertex) {
    for(auto edge : currentVertex->getIncidentEdges()) {
        if(edge->contains(startVertex))
            return edge;
    }
}