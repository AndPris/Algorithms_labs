#include <iostream>
#include "graph.h"
#include "random_generators.h"
#include "GASolver.h"

using namespace std;

int main() {
	srand(time(nullptr));

	int amountOfVertexes = 300;
	Graph a(amountOfVertexes);
	//a.display();

	vector<Vertex*> vertexes = a.getVertexes();

	GASolver solver(&a, vertexes.at(0), vertexes.at(290));
	solver.solve();

	return 0;
}