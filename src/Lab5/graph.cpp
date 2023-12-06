#include "graph.h"

Graph::Graph(int amountOfVertexes) {
    this->amountOfVertexes = amountOfVertexes;
    generateVertexes();
    generateEdges();
}

void Graph::generateVertexes() {
    for (int i = 0; i < amountOfVertexes; ++i) {
        Vertex* vertex = new Vertex(i + 1);
        vertexes.push_back(vertex);
    }
}

void Graph::generateEdges() {
    for (int i = 0; i < amountOfVertexes; ++i) {
        int vertexDegree = generateNumberInRange(MIN_DEGREE, MAX_DEGREE/2);
        for (int j = i + 1; j < i + 1 + vertexDegree && j < amountOfVertexes; ++j) {
            int length = generateNumberInRange(MIN_LENGTH, MAX_LENGTH);

            Edge* edge = new Edge(vertexes.at(i), vertexes.at(j), length);
            edges.push_back(edge);

            vertexes.at(i)->addIncidentEdge(edge);
            vertexes.at(j)->addIncidentEdge(edge);
        }
    }
}

int Graph::getAmountOfVertexes() const {
    return  amountOfVertexes;
}

vector<Vertex*> Graph::getVertexes() {
    return vertexes;
}

vector<Edge*> Graph::getEdges() {
    return edges;
}

Edge* Graph::getEdgeWithVertexes(Vertex* vertex1, Vertex* vertex2) {
    for (auto& edge : edges) {
        if (edge->contains(vertex1) && edge->contains(vertex2))
            return edge;
    }

    return nullptr;
}

Vertex* Graph::getVertexWithNumber(int number) {
    for (auto vertex : vertexes) {
        if (vertex->getNumber() == number)
            return vertex;
    }

    return nullptr;
}

void Graph::display() {
    const int amountOfDisplayedVertexes = 5;
    const int width = 3;

    displayVertexesInTop(width, amountOfDisplayedVertexes);

    for (int i = 0; i < amountOfDisplayedVertexes; ++i)
        displayFirstAndLastEdges(i, amountOfDisplayedVertexes, width);

    for (int i = 0; i < amountOfDisplayedVertexes * 2 + 2; ++i)
        cout << "... ";
    cout << endl;

    for (int i = amountOfVertexes - amountOfDisplayedVertexes; i < amountOfVertexes; ++i)
        displayFirstAndLastEdges(i, amountOfDisplayedVertexes, width);
}

void Graph::displayFirstAndLastEdges(int vertexIndex, int amount, int width) {
    cout << setw(width) << vertexes.at(vertexIndex)->getNumber() << " ";
    displayEdgeLength(vertexIndex, 0, amount, width);
    cout << "... ";
    displayEdgeLength(vertexIndex, amountOfVertexes - amount, amountOfVertexes, width);
    cout << endl;
}
void Graph::displayVertexesInTop(int width, int amountOfDisplayedVertexes) {
    cout << setw(width) << "" << " ";
    for (int i = 0; i < amountOfDisplayedVertexes; ++i)
        cout << setw(width) << vertexes.at(i)->getNumber() << " ";
    cout << "... ";
    for (int i = amountOfVertexes - amountOfDisplayedVertexes; i < amountOfVertexes; ++i)
        cout << setw(width) << vertexes.at(i)->getNumber() << " ";
    cout << endl;
}
void Graph::displayEdgeLength(int vertexIndex, int from, int to, int width) {
    for (int j = from; j < to; ++j) {
        if (vertexIndex == j) {
            cout << setw(width) << "0" << " ";
            continue;
        }
        Edge* edge = getEdgeWithVertexes(vertexes.at(vertexIndex), vertexes.at(j));
        if (!edge)
            cout << setw(width) << "-" << " ";
        else
            cout << setw(width) << edge->getLength() << " ";
    }
}

Graph::~Graph() {
    for (auto vertex : vertexes)
        delete vertex;
    for (auto edge : edges)
        delete edge;
}