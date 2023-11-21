#include "ACO_TSP_Solver.h"

ACO_TSP_Solver::ACO_TSP_Solver(FullGraph *&graph) {
    graphToSolve = graph;
    amountOfAnts = AMOUNT_OF_ANTS;
    amountOfEliteAnts = AMOUNT_OF_ELITE_ANTS;
    amountOfIterations = AMOUNT_OF_ITERATIONS;
}

Path ACO_TSP_Solver::solve() {
    calculateOptimalCycleLength();

    placeAnts();

    for(int i = 0; i < amountOfIterations; ++i) {
        buildCyclesForAnts();
        findCurrentEliteAnts();
        currentBestCycle = ants.at(0)->getPath();
        renewPheromone();
        clearAntsPathes();
    }

    return currentBestCycle;
}
void ACO_TSP_Solver::calculateOptimalCycleLength() {
    TSPGreedySolver solver(graphToSolve);
    Path greedyResult = solver.solve();
    optimalCycleLength = greedyResult.getLength();
}
void ACO_TSP_Solver::placeAnts() {
    vector<Vertex*> graphVertexes = graphToSolve->getVertexes();

    for(int i = 0; i < amountOfAnts; ++i) {
        int vertexIndex = generateNumberInRange(0, graphVertexes.size()-1);
        Ant* ant = new Ant(graphVertexes.at(vertexIndex), optimalCycleLength, PHEROMONE_DEGREE, VISIBILITY_DEGREE);
        ants.push_back(ant);
        graphVertexes.erase(graphVertexes.begin() + vertexIndex);
    }
}
void ACO_TSP_Solver::buildCyclesForAnts() {
    for(auto ant : ants) {
        for(int i = 0; i < graphToSolve->getAmountOfVertexes(); ++i)
            ant->move();
    }
}
void ACO_TSP_Solver::findCurrentEliteAnts() {
    sort(ants.begin(), ants.end(), [](Ant* a, Ant* b) {return a->getPath() < b->getPath();});

    currentEliteAnts.clear();
    for(int i = 0; i < amountOfEliteAnts; ++i)
        currentEliteAnts.push_back(ants.at(i));
}
void ACO_TSP_Solver::renewPheromone() {
    for(auto edge : graphToSolve->getEdges())
        edge->evaporatePheromone();

    for(auto eliteAnt : currentEliteAnts)
        eliteAnt->extractPheromone();

    for(auto ant : ants)
        ant->extractPheromone();
}
void ACO_TSP_Solver::clearAntsPathes() {
    for(auto ant : ants)
        ant->clearPath();
}

int ACO_TSP_Solver::getOptimalCycleLength() const {
    return optimalCycleLength;
}

ACO_TSP_Solver::~ACO_TSP_Solver() {
    for(auto ant : ants)
        delete ant;
}