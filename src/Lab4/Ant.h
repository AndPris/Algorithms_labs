#pragma once

#include "Vertex_Edge_Path.h"
#include "Random_generators.h"
#include <math.h>


class Ant {
    int optimalCycleLength;
    Vertex* startVertex;
    Vertex* currentVertex;
    Path path;
    int pheromoneDegree;
    int visibilityDegree;

    Edge* selectNextEdgeToMove();
    double calculateSelectionValue(Edge* edge);
    vector<Edge*> getPossibleNextEdges(float &generalSelectionValue);
    Edge* getLastPossibleEdge();
public:
    Ant(Vertex* startVertex, int optimalCycleLength, int pheromoneDegree, int visibilityDegree);

    void move();
    void extractPheromone();

    Path getPath();
    void clearPath();

    Ant& operator=(const Ant& obj);
};
