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

vector<Vertex*> Chromosome::getVertexes() {
	return vertexes;
}

bool Chromosome::contains(Vertex* vertex) {
	for (auto vert : vertexes) {
		if (vert == vertex)
			return true;
	}

	return false;
}

vector<int> Chromosome::findPositionsOfIntersection(Chromosome* obj) const {
	vector<int> positionsOfIntersection;

	for (int i = 1; i < vertexes.size() - 1; ++i) {
		for (int j = 1; j < obj->vertexes.size() - 1; ++j) {
			if (vertexes.at(i) == obj->vertexes.at(j)) {
				positionsOfIntersection.push_back(i);
				positionsOfIntersection.push_back(j);
				return positionsOfIntersection;
			}
		}
	}

	return positionsOfIntersection;
}

void Chromosome::replace(int begin, int end, Chromosome* newPath) {
	vertexes.erase(vertexes.begin() + begin, vertexes.begin() + end + 1);
	vertexes.insert(vertexes.begin() + begin, newPath->vertexes.begin(), newPath->vertexes.end());
}

void Chromosome::deleteLastVertex() {
	vertexes.pop_back();
}

void Chromosome::display() const {
	for (int i = 0; i < vertexes.size()-1; ++i)
		cout << vertexes.at(i)->getNumber() << " -> ";
	cout << vertexes.back()->getNumber() << endl;
}

bool Chromosome::operator==(const Chromosome& obj) {
	if (vertexes.size() != obj.vertexes.size())
		return false;

	for (int i = 0; i < vertexes.size(); ++i) {
		if (vertexes.at(i) != obj.vertexes.at(i))
			return false;
	}

	return true;
}
