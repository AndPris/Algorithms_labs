#include "vertex_edge.h"

Vertex::Vertex(int number) {
    this->number = number;
}

bool Vertex::operator==(const Vertex& obj) {
    return this->number == obj.number;
}

void Vertex::addIncidentEdge(Edge* edgeToAdd) {
    incidentEdges.push_back(edgeToAdd);
}

Edge* Vertex::getConnectingEdge(Vertex* connectedVertex) {
    for (auto edge : incidentEdges) {
        if (edge->contains(connectedVertex))
            return edge;
    }

    return nullptr;
}

vector<Edge*> Vertex::getIncidentEdges() {
    return incidentEdges;
}

int Vertex::getNumber() {
    return number;
}


Edge::Edge(Vertex* vertex1, Vertex* vertex2, int length) {
    connectedVertexes.push_back(vertex1);
    connectedVertexes.push_back(vertex2);
    this->length = length;
}

int Edge::getLength() const {
    return length;
}

vector<Vertex*> Edge::getConnectedVertexes() {
    return connectedVertexes;
}

bool Edge::operator==(const Edge& obj) {
    return (this->connectedVertexes.at(0) == obj.connectedVertexes.at(0) &&
        this->connectedVertexes.at(1) == obj.connectedVertexes.at(1)) ||
        (this->connectedVertexes.at(0) == obj.connectedVertexes.at(1) &&
            this->connectedVertexes.at(1) == obj.connectedVertexes.at(0));
}

bool Edge::contains(Vertex* vertex) const {
    return (*connectedVertexes.at(0) == *vertex) ||
        (*connectedVertexes.at(1) == *vertex);
}