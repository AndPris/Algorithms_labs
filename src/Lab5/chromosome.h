#pragma once

#include "vertex_edge.h"
#include <iostream>

using namespace std;


class Chromosome {
	vector<Vertex*> vertexes;

public:
	void addVertex(Vertex* vertex);

	bool contains(Vertex* vertex);
	void deleteLastVertex();

	int getLength() const;
	vector<Vertex*> getVertexes();
	vector<int> findPositionsOfIntersection(Chromosome* obj) const;

	void replace(int begin, int end, Chromosome* newPath);

	void display() const;

	bool operator==(const Chromosome& obj);
};