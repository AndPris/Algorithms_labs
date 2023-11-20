#include "FullGraph.h"
#include "ACO_TSP_Solver.h"
#include "Input_Validators.h"

#define AMOUNT_OF_VERTEXES 200

void displayWelcomeInfo();

int main() {
    srand(time(nullptr));
    
    displayWelcomeInfo();
    int run;
    do {
        FullGraph graph(AMOUNT_OF_VERTEXES);
        FullGraph* graphPointer = &graph;

        ACO_TSP_Solver solver(graphPointer);
        Path result = solver.solve();
        cout << "Greedy algorithm length: " << solver.getOptimalCycleLength() << endl;
        cout << "Ant colony optimization solution:" << endl;
        result.display();

        cout << "Enter 0 to stop the program of 1 to run it again" << endl;
        run = inputPositiveNumberInRange(0, 1);
    } while (run);
    return 0;
}

void displayWelcomeInfo() {
    cout << "This program implements Ant Colony Optimization algorithm for solving Traveling Salesman Problem" << endl;
    cout << "Amount of vertexes in graph: " << AMOUNT_OF_VERTEXES << endl;
    cout << "a (pheromone degree): " << PHEROMONE_DEGREE << endl;
    cout << "b (visibility degree): " << VISIBILITY_DEGREE << endl;
    cout << "p (evaporation coefficient: " << EVAPORATION_COEFFICIENT << endl;
    cout << "Amount of ants: " << AMOUNT_OF_ANTS << endl;
    cout << "Amount of elite ants: " << AMOUNT_OF_ELITE_ANTS << endl;
    cout << "Amount of iterations: " << AMOUNT_OF_ITERATIONS << endl;
}
