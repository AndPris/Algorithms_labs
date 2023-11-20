#include "FullGraph.h"
#include "ACO_TSP_Solver.h"

int main() {
    srand(time(nullptr));
    const int amountOfVertexes = 200;

    FullGraph graph(amountOfVertexes);
//    graph.display();
    FullGraph* graphPointer = &graph;

    ACO_TSP_Solver solver(graphPointer);
    Path result = solver.solve();
    result.display();
    return 0;
}
