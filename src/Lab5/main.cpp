#include <iostream>
#include "graph.h"
#include "random_generators.h"
#include "GASolver.h"

using namespace std;

int main() {
	srand(time(nullptr));

	int amountOfVertexes = 10;
	Graph a(amountOfVertexes);
	a.display();

	vector<Vertex*> vertexes = a.getVertexes();

	GASolver(&a, vertexes.at(0), vertexes.at(7));

	return 0;
}