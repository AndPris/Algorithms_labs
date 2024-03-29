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
    void displayVertexesInTop(int width, int amountOfDisplayedVertexes);
    void displayEdgeLength(int vertexIndex, int from, int to, int width);
    void displayFirstAndLastEdges(int vertexIndex, int amount, int width);
public:
    FullGraph(int amountOfVertexes);

    int getAmountOfVertexes() const;
    vector<Vertex*> getVertexes();
    vector<Edge*> getEdges();

    void display();
    Edge* getEdgeWithVertexes(Vertex* vertex1, Vertex* vertex2);

    ~FullGraph();
};
