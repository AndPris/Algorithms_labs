#include "chromosome.h"

void Chromosome::addVertex(Vertex* vertex) {
	vertexes.push_back(vertex);
}

int Chromosome::getLength() const {
	int length = 0;

	for (int i = 0; i < vertexes.size() - 1; ++i) {
		auto edge = vertexes.at(i)->getConnectingEdge(vertexes.at(i + 1));
		length += edge->getLength();
	}

	return length;
}

bool Chromosome::contains(Vertex* vertex) {
	for (auto vert : vertexes) {
		if (vert == vertex)
			return true;
	}

	return false;
}

void Chromosome::deleteLastVertex() {
	vertexes.pop_back();
}

void Chromosome::display() const {
	for (int i = 0; i < vertexes.size() - 1; ++i)
		cout << vertexes.at(i)->getNumber() << " -> " << vertexes.at(i + 1)->getNumber() << ", ";
	cout << endl;
}