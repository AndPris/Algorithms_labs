#include "Ant.h"

Ant::Ant(Vertex *startVertex, int optimalCycleLength, int pheromoneDegree, int visibilityDegree) : optimalCycleLength(optimalCycleLength) {
    this->startVertex = startVertex;
    this->currentVertex = startVertex;
    this->pheromoneDegree = pheromoneDegree;
    this->visibilityDegree = visibilityDegree;
}

void Ant::move() {
    Edge* nextEdge;
    nextEdge = selectNextEdgeToMove();
    path.addEdge(nextEdge);

    vector<Vertex*> nextEdgeConnectedVertexes;
    nextEdgeConnectedVertexes = nextEdge->getConnectedVertexes();

    if(*currentVertex == *nextEdgeConnectedVertexes[0])
        currentVertex = nextEdgeConnectedVertexes[1];
    else
        currentVertex = nextEdgeConnectedVertexes[0];
}

Edge *Ant::selectNextEdgeToMove() {
    double nextEdgeSelector = generateDoubleNumberInRange(0, 1);

    float generalSelectionValue = 0;
    vector<Edge*> possibleNextEdges = getPossibleNextEdges(generalSelectionValue);

    if(possibleNextEdges.empty()) {
        possibleNextEdges.push_back(getLastPossibleEdge());
        generalSelectionValue = calculateSelectionValue(possibleNextEdges[0]);
    }

    for(auto edge : possibleNextEdges) {
        double selectionPossibility = calculateSelectionValue(edge) / generalSelectionValue;
        nextEdgeSelector -= selectionPossibility;

        if(nextEdgeSelector <= 0)
            return edge;
    }

    return possibleNextEdges.back();
}
double Ant::calculateSelectionValue(Edge *edge) {
    double pheromoneContribution = pow(edge->getAmountOfPheromone(), pheromoneDegree);
    double visibilityContribution = pow((1.0 / edge->getLength()), visibilityDegree);
    return pheromoneContribution*visibilityContribution;
}
vector<Edge *> Ant::getPossibleNextEdges(float &generalSelectionValue) {
    vector<Edge*> possibleNextEdges;

    for(auto edge : currentVertex->getIncidentEdges()) {
        if(path.containsVertexes(edge->getConnectedVertexes()))
            continue;
        possibleNextEdges.push_back(edge);
        generalSelectionValue += calculateSelectionValue(edge);
    }

    return possibleNextEdges;
}
Edge *Ant::getLastPossibleEdge() {
    for(auto edge : currentVertex->getIncidentEdges()) {
        if(edge->contains(startVertex))
            return edge;
    }
}


void Ant::extractPheromone() {
    double additionalAmountOfPheromone = (double)optimalCycleLength/path.getLength();
    for(int i = 0; i < path.getAmountOfEdges(); ++i)
        path[i]->addPheromone(additionalAmountOfPheromone);
}

Path Ant::getPath() {
    return path;
}

void Ant::clearPath() {
    path.clear();
}

Ant &Ant::operator=(const Ant &obj) {
    optimalCycleLength = obj.optimalCycleLength;
    startVertex = obj.startVertex;
    currentVertex = obj.currentVertex;
    path = obj.path;
    pheromoneDegree = obj.pheromoneDegree;
    visibilityDegree = obj.visibilityDegree;

    return *this;
}