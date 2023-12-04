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

	void display() const;
};