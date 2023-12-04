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

vector<Edge*> Vertex::getIncidentEdges() {
    return incidentEdges;
}
int Vertex::getNumber() {
    return number;
}


Edge::Edge(Vertex* vertex1, Vertex* vertex2, int length, float amountOfPheromone, float evaporationCoefficient) {
    connectedVertexes.push_back(vertex1);
    connectedVertexes.push_back(vertex2);
    this->length = length;
    this->amountOfPheromone = amountOfPheromone;
    this->evaporationCoefficient = evaporationCoefficient;
}

void Edge::addPheromone(float additionalPheromone) {
    amountOfPheromone += additionalPheromone;
}
void Edge::evaporatePheromone() {
    amountOfPheromone = (1 - evaporationCoefficient) * amountOfPheromone;
}

int Edge::getLength() const {
    return length;
}
float Edge::getAmountOfPheromone() const {
    return amountOfPheromone;
}
vector<Vertex*> Edge::getConnectedVertexes() {
    return connectedVertexes;
}
bool Edge::operator==(const Edge& obj) {
    return (this->connectedVertexes[0] == obj.connectedVertexes[0] &&
        this->connectedVertexes[1] == obj.connectedVertexes[1]) ||
        (this->connectedVertexes[0] == obj.connectedVertexes[1] &&
            this->connectedVertexes[1] == obj.connectedVertexes[0]);
}

bool Edge::contains(Vertex* vertex) const {
    return (*connectedVertexes[0] == *vertex) ||
        (*connectedVertexes[1] == *vertex);
}