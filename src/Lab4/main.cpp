#include "FullGraph.h"
#include "ACO_TSP_Solver.h"

int main() {
    srand(time(nullptr));
    const int amountOfVertexes = 200;

    FullGraph graph(amountOfVertexes);
    FullGraph* graphPointer = &graph;

    ACO_TSP_Solver solver(graphPointer);
    Path result = solver.solve();
    cout << "Greedy algorithm length: " << solver.getOptimalCycleLength() << endl;
    cout << "Ant colony optimization solution:" << endl;
    result.display();
    return 0;
}
