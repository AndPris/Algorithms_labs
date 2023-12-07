#pragma once

#include "graph.h"
#include "chromosome.h"
#include <algorithm>

#define AMOUNT_OF_ITERATIONS 120
#define POPULATION_SIZE 130
#define MUTATION_CHANCE 75


class GASolver {
	int populationSize;
	int mutationChance;
	int amountOfIterations;

	Graph* graphToSolve;

	Vertex *source, *destination;

	vector<Chromosome*> population;
	Chromosome* currentBestChromosome;


	bool getRandomPath(Vertex* startVertex, Vertex* endVertex, Chromosome *&path, Chromosome *&deadEndVertexes);
	vector<Vertex*> getPossibleNextVertexes(Vertex* currentVertex, Vertex* endVertex, Chromosome* visitedVertexes, Chromosome* deadEndVertexes);

	void createInitialPopulation();
	void findCurrentBestChromosome();

	Chromosome* crossover(Chromosome* parent1, Chromosome* parent2);
	Chromosome* getRandomChromosomeForCrossover();

	void mutate(Chromosome* chromosome);
	void deleteTheWorstChromosome();
public:
	GASolver(Graph* graph, Vertex* source, Vertex* destination);

	Chromosome* solve();

	~GASolver();
};