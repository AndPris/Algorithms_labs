#pragma once

#include "graph.h"
#include "chromosome.h"
#include <algorithm>

#define POPULATION_SIZE 10
#define AMOUNT_OF_ITERATIONS 100

class GASolver {
	int populationSize;

	Graph* graphToSolve;

	Vertex *source, *destination;

	vector<Chromosome*> population;
	Chromosome* currentBestChromosome;


	bool getRandomPath(Vertex* startVertex, Vertex* endVertex, Chromosome *&path);
	vector<Vertex*> getPossibleNextVertexes(Vertex* currentVertex, Chromosome* visitedVertexes);

	void createInitialPopulation();
	void findCurrentBestChromosome();

	Chromosome* crossover(Chromosome* parent1, Chromosome* parent2);
	Chromosome* getRandomChromosomeForCrossover();
public:
	GASolver(Graph* graph, Vertex* source, Vertex* destination);

	void solve();

	~GASolver();
};