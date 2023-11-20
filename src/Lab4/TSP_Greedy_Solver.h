#pragma once

#include "FullGraph.h"

class TSPGreedySolver {
    FullGraph* graphToSolve;

    Edge* findTheShortestEdge(Vertex* vertexes, Path& passedPath);
    void selectNextVertex(Vertex*& currentVertex, Edge* edge);
    Edge* findLastEdge(Vertex* startVertex, Vertex* currentVertex);
public:
    TSPGreedySolver(FullGraph*& graph);

    Path solve();
};