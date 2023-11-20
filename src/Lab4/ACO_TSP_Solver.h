#pragma once

#include "Ant.h"
#include "FullGraph.h"
#include "TSP_Greedy_Solver.h"
#include <algorithm>

//TODO: set correct values
#define AMOUNT_OF_ANTS 45
#define AMOUNT_OF_ELITE_ANTS 10
#define PHEROMONE_DEGREE 3
#define VISIBILITY_DEGREE 2
#define AMOUNT_OF_ITERATIONS 5


class ACO_TSP_Solver {
    FullGraph* graphToSolve;
    int amountOfAnts;
    int amountOfEliteAnts;
    int optimalCycleLength;
    int amountOfIterations;
    vector<Ant*> ants;

    vector<Ant*> currentEliteAnts;
    Path currentBestCycle;

    void placeAnts();
    void buildCyclesForAnts();
    void findCurrentEliteAnts();
    void renewPheromone();
public:
    ACO_TSP_Solver(FullGraph*& graph);

    Path solve();

    ~ACO_TSP_Solver();
};
