#include "graph.h"
#include "random_generators.h"
#include "GASolver.h"
#include "input_validators.h"

using namespace std;

int main() {
	srand(time(nullptr));
	const int amountOfVertexes = 300;

	Graph graph(amountOfVertexes);
	graph.display();

	vector<Vertex*> vertexes = graph.getVertexes();
	int run;
	do {
		int start = 1;//generateNumberInRange(0, amountOfVertexes / 2);
			int finish = 2;//generateNumberInRange(start + 1, amountOfVertexes - 1);

		GASolver solver(&graph, vertexes.at(start), vertexes.at(finish));
		Chromosome* solution = solver.solve();
		cout << "The shortest path between vertexes " << start+1 << " and " << finish+1 << " is:" << endl;
		solution->display();
		cout << "Length: " << solution->getLength() << endl;

		cout << "Enter 1 to run the program again or 0 to exit:" << endl;
		run = inputPositiveNumberInRange(0, 1);
	} while (run);
	return 0;
}