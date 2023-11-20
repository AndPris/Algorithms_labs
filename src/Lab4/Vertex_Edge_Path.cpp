#include "Vertex_Edge_Path.h"

Vertex::Vertex(int number) {
    this->number = number;
}

bool Vertex::operator==(const Vertex &obj) {
    return this->number == obj.number;
}
void Vertex::addIncidentEdge(Edge *edgeToAdd) {
    incidentEdges.push_back(edgeToAdd);
}

vector<Edge *> Vertex::getIncidentEdges() {
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
    amountOfPheromone = (1-evaporationCoefficient)*amountOfPheromone;
}

int Edge::getLength() const {
    return length;
}
float Edge::getAmountOfPheromone() const {
    return amountOfPheromone;
}
vector<Vertex *> Edge::getConnectedVertexes() {
    return connectedVertexes;
}
bool Edge::operator==(const Edge &obj) {
    return (this->connectedVertexes[0] == obj.connectedVertexes[0] &&
            this->connectedVertexes[1] == obj.connectedVertexes[1]) ||
            (this->connectedVertexes[0] == obj.connectedVertexes[1] &&
             this->connectedVertexes[1] == obj.connectedVertexes[0]);
}

bool Edge::contains(Vertex *vertex) const {
    return (*connectedVertexes[0] == *vertex) ||
            (*connectedVertexes[1] == *vertex);
}

Path::Path() {
    amountOfEdges = 0;
    length = 0;
}
void Path::addEdge(Edge *edge) {
    ++amountOfEdges;
    length += edge->getLength();
    edges.push_back(edge);
}

void Path::clear() {
    amountOfEdges = 0;
    length = 0;
    edges.clear();
}

int Path::getLength() const {
    return length;
}

int Path::getAmountOfEdges() const {
    return amountOfEdges;
}

Edge *&Path::operator[](int index) {
    return edges.at(index);
}

bool Path::containsVertexes(vector<Vertex *> vertexes) const {
    for(auto vertex : vertexes) {
        bool contains = false;

        for(auto edge : edges) {
            if(edge->contains(vertex)) {
                contains = true;
                break;
            }
        }

        if(!contains)
            return false;
    }

    return true;
}

bool Path::operator<(const Path &obj) {
    return length < obj.length;
}

void Path::display() {
    Vertex *vertex1, *vertex2;
    vector<Vertex*> connectedVertexes1 = edges.at(0)->getConnectedVertexes();
    vector<Vertex*> connectedVertexes2 = edges.at(1)->getConnectedVertexes();
    if((connectedVertexes1.at(0) == connectedVertexes2.at(0)) || (connectedVertexes1.at(0) == connectedVertexes2.at(1))) {
        vertex1 = connectedVertexes1.at(1);
        vertex2 = connectedVertexes1.at(0);
    } else {
        vertex1 = connectedVertexes1.at(0);
        vertex2 = connectedVertexes1.at(1);
    }
    cout<<vertex1->getNumber()<<" -> "<<vertex2->getNumber()<<", ";
    for(int i = 1; i < edges.size(); ++i) {
        connectedVertexes1 = edges.at(i)->getConnectedVertexes();

        if(connectedVertexes1.at(0) == vertex2) {
            vertex1 = connectedVertexes1.at(0);
            vertex2 = connectedVertexes1.at(1);
        } else {
            vertex1 = connectedVertexes1.at(1);
            vertex2 = connectedVertexes1.at(0);
        }
        cout<<vertex1->getNumber()<<" -> "<<vertex2->getNumber()<<", ";
    }
    cout<<endl<<"Length: "<<length<<endl;
}
