#pragma once

#include "Vertex_Edge_Path.h"
#include "Random_generators.h"
#include <iostream>
#include <iomanip>

#define EVAPORATION_COEFFICIENT 0.7
#define MAX_WEIGHT 40

class FullGraph {
    int amountOfVertexes;

    vector<Vertex*> vertexes;
    vector<Edge*> edges;

    void generateVertexes();
    void generateEdges();
public:
    FullGraph(int amountOfVertexes);

    int getAmountOfVertexes() const;
    vector<Vertex*> getVertexes();
    vector<Edge*> getEdges();

    void display();
    Edge* getEdgeWithVertexes(Vertex* vertex1, Vertex* vertex2);

    ~FullGraph();
};
