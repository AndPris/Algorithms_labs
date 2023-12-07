#pragma once

#include "vertex_edge.h"
#include "random_generators.h"
#include <iostream>
#include <iomanip>

#define MIN_DEGREE 1
#define MAX_DEGREE 10
#define MIN_LENGTH 5
#define MAX_LENGTH 150

class Graph {
    int amountOfVertexes;

    vector<Vertex*> vertexes;
    vector<Edge*> edges;

    void generateVertexes();
    void generateEdges();
    void displayVertexesInTop(int width, int amountOfDisplayedVertexes);
    void displayEdgeLength(int vertexIndex, int from, int to, int width);
    void displayFirstAndLastEdges(int vertexIndex, int amount, int width);
public:
    Graph(int amountOfVertexes);

    int getAmountOfVertexes() const;
    vector<Vertex*> getVertexes();
    Vertex* getVertexWithNumber(int number);

    vector<Edge*> getEdges();

    void display();
    Edge* getEdgeWithVertexes(Vertex* vertex1, Vertex* vertex2);

    ~Graph();
};
