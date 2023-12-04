#pragma once

#include "graph.h"
#include "chromosome.h"

#define POPULATION_SIZE 5

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
public:
	GASolver(Graph* graph, Vertex* source, Vertex* destination);

	~GASolver();
};