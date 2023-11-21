#pragma once

#include <vector>
#include <iostream>
using namespace std;

class Vertex;
class Edge;


class Vertex {
    vector<Edge*> incidentEdges;
    int number;
public:
    Vertex(int number);

    void addIncidentEdge(Edge* edgeToAdd);
    vector<Edge*> getIncidentEdges();
    int getNumber();

    bool operator==(const Vertex& obj);
};


class Edge {
    vector<Vertex*> connectedVertexes;
    int length;
    float amountOfPheromone;
    float evaporationCoefficient;
public:
    Edge(Vertex* vertex1, Vertex* vertex2, int length, float amountOfPheromone, float evaporationCoefficient);

    void evaporatePheromone();
    void addPheromone(float additionalPheromone);

    int getLength() const;
    float getAmountOfPheromone() const;
    bool contains(Vertex* vertex) const;

    vector<Vertex*> getConnectedVertexes();
    bool operator==(const Edge& obj);
};

class Path {
    vector<Edge*> edges;
    int amountOfEdges;
    int length;
public:
    Path();

    void addEdge(Edge* edge);
    void clear();

    Edge*& operator[](int index);
    int getAmountOfEdges() const;
    int getLength() const;

    bool containsVertexes(vector<Vertex*> vertexes) const;
    bool operator<(const Path& obj);

    void display();
};