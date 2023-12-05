#pragma once

#include "graph.h"
#include "chromosome.h"
#include <algorithm>

#define POPULATION_SIZE 30
#define AMOUNT_OF_ITERATIONS 400

class GASolver {
	int populationSize;

	Graph* graphToSolve;

	Vertex *source, *destination;

	vector<Chromosome*> population;
	Chromosome* currentBestChromosome;


	bool getRandomPath(Vertex* startVertex, Vertex* endVertex, Chromosome *&path);
	vector<Vertex*> getPossibleNextVertexes(Vertex* currentVertex, Vertex* endVertex, Chromosome* visitedVertexes);

	void createInitialPopulation();
	void findCurrentBestChromosome();

	Chromosome* crossover(Chromosome* parent1, Chromosome* parent2);
	Chromosome* getRandomChromosomeForCrossover();

	void mutate(Chromosome* chromosome);
	void deleteTheWorstChromosome();
public:
	GASolver(Graph* graph, Vertex* source, Vertex* destination);

	void solve();

	~GASolver();
};