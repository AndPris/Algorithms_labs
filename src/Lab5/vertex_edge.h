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
    Edge* getConnectingEdge(Vertex* connectedVertex);
    int getNumber();

    bool operator==(const Vertex& obj);
};


class Edge {
    vector<Vertex*> connectedVertexes;
    int length;
public:
    Edge(Vertex* vertex1, Vertex* vertex2, int length);

    int getLength() const;
    bool contains(Vertex* vertex) const;

    vector<Vertex*> getConnectedVertexes();
    bool operator==(const Edge& obj);
};