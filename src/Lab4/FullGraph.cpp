#include "FullGraph.h"

FullGraph::FullGraph(int amountOfVertexes) {
    this->amountOfVertexes = amountOfVertexes;
    generateVertexes();
    generateEdges();
}
void FullGraph::generateVertexes() {
    for(int i = 0; i < amountOfVertexes; ++i) {
        Vertex* vertex = new Vertex(i+1);
        vertexes.push_back(vertex);
    }
}
void FullGraph::generateEdges() {
    for(int i = 0; i < amountOfVertexes; ++i) {
        for(int j = i+1; j < amountOfVertexes; ++j) {
            int length = generateNumberInRange(1, MAX_WEIGHT);
            double amountOfPheromone = generateDoubleNumberInRange(0, 1);

            Edge* edge = new Edge(vertexes.at(i), vertexes.at(j), length, amountOfPheromone, EVAPORATION_COEFFICIENT);
            edges.push_back(edge);

            vertexes.at(i)->addIncidentEdge(edge);
            vertexes.at(j)->addIncidentEdge(edge);
        }
    }
}

int FullGraph::getAmountOfVertexes() const {
    return  amountOfVertexes;
}

vector<Vertex *> FullGraph::getVertexes() {
    return vertexes;
}
vector<Edge *> FullGraph::getEdges() {
    return edges;
}

void FullGraph::display() {
    const int width = 3;

    cout<<setw(width)<<""<<" ";
    for(int i = 0; i < amountOfVertexes; ++i)
        cout<<setw(width)<<vertexes.at(i)->getNumber()<<" ";
    cout<<endl;

    for(int i = 0; i < amountOfVertexes; ++i) {
        cout<<setw(width)<<vertexes.at(i)->getNumber()<<" ";

        for(int j = 0; j < amountOfVertexes; ++j) {
            if(i == j) {
                cout<<setw(width)<<"0"<<" ";
                continue;
            }
            Edge* edge = getEdgeWithVertexes(vertexes.at(i), vertexes.at(j));
            cout<<setw(width)<<edge->getLength()<<" ";
        }

        cout<<endl;
    }
}

Edge *FullGraph::getEdgeWithVertexes(Vertex *vertex1, Vertex *vertex2) {
    for(auto &edge : edges) {
        if(edge->contains(vertex1) && edge->contains(vertex2))
            return edge;
    }

    return nullptr;
}

FullGraph::~FullGraph() {
    for(auto vertex : vertexes)
        delete vertex;
    for(auto edge : edges)
        delete edge;
}