#include "GASolver.h"

GASolver::GASolver(Graph* graph, Vertex* source, Vertex* destination) {
	this->graphToSolve = graph;
	this->source = source;
	this->destination = destination;
	this->populationSize = POPULATION_SIZE;
	this->mutationChance = MUTATION_CHANCE;
	this->amountOfIterations = AMOUNT_OF_ITERATIONS;

	createInitialPopulation();
	findCurrentBestChromosome();
}

void GASolver::createInitialPopulation() {
	Chromosome* deadEndVertexes = new Chromosome;
	for (int i = 0; i < populationSize; ++i) {
		Chromosome* path = new Chromosome;
		Vertex* startVertex = source;
		Vertex* endVertex = destination;
		getRandomPath(source, destination, path, deadEndVertexes);
		population.push_back(path);
	}
	delete deadEndVertexes;
}

void GASolver::findCurrentBestChromosome() {
	currentBestChromosome = population.at(0);

	for (int i = 1; i < population.size(); ++i) {
		if (population.at(i)->getLength() < currentBestChromosome->getLength())
			currentBestChromosome = population.at(i);
	}
}

bool GASolver::getRandomPath(Vertex* startVertex, Vertex* endVertex, Chromosome*& path, Chromosome*& deadEndVertexes) {
	if (startVertex == endVertex) {
		path->addVertex(startVertex);
		return true;
	}
	
	path->addVertex(startVertex);

	vector<Vertex*> possibleNextVertexes = getPossibleNextVertexes(startVertex, endVertex, path, deadEndVertexes);

	if (possibleNextVertexes.empty()) {
		deadEndVertexes->addVertex(startVertex);
		path->deleteLastVertex();
		return false;
	}

	random_shuffle(possibleNextVertexes.begin(), possibleNextVertexes.end());

	for (auto vertex : possibleNextVertexes) {
		if (getRandomPath(vertex, endVertex, path, deadEndVertexes))
			return true;
	}

	path->deleteLastVertex();
	deadEndVertexes->addVertex(startVertex);
	return false;
}

vector<Vertex*> GASolver::getPossibleNextVertexes(Vertex* currentVertex, Vertex* endVertex, Chromosome* visitedVertexes, Chromosome* deadEndVertexes) {
	vector<Vertex*> possibleNextVertexes;

	for (auto edge : currentVertex->getIncidentEdges()) {
		Vertex* nextVertex;
		vector<Vertex*> connectedVertexes = edge->getConnectedVertexes();

		if (currentVertex == connectedVertexes.at(0))
			nextVertex = connectedVertexes.at(1);
		else
			nextVertex = connectedVertexes.at(0);

		if (!visitedVertexes->contains(nextVertex) && !deadEndVertexes->contains(nextVertex))
			possibleNextVertexes.push_back(nextVertex);
	}

	return possibleNextVertexes;
}

Chromosome* GASolver::solve() {
	for (int i = 0; i < amountOfIterations; ++i) {
		Chromosome* randomChromosomeForCrossover = getRandomChromosomeForCrossover();
		Chromosome* childChromosome = crossover(currentBestChromosome, randomChromosomeForCrossover);
		
		int mutationValue = generateNumberInRange(1, 100);
		if(mutationValue <= mutationChance)
			mutate(childChromosome);

		population.push_back(childChromosome);

		if (childChromosome->getLength() <= currentBestChromosome->getLength())
			currentBestChromosome = childChromosome;
		
		deleteTheWorstChromosome();
	}

	return currentBestChromosome;
}

Chromosome* GASolver::crossover(Chromosome* parent1, Chromosome* parent2) {
	Chromosome* child = new Chromosome;
	vector<Vertex*> parent1Vertexes = parent1->getVertexes();
	vector<Vertex*> parent2Vertexes = parent2->getVertexes();

	vector<int> positionsOfIntersection = parent1->findPositionsOfIntersection(parent2);
	if (positionsOfIntersection.empty()) {
		for (int i = 0; i < parent2Vertexes.size(); ++i)
			child->addVertex(parent2Vertexes.at(i));
		return child;
	}

	int pos1 = positionsOfIntersection.at(0);
	int pos2 = positionsOfIntersection.at(1);

	for (int i = 0; i < pos1; ++i)
		child->addVertex(parent1Vertexes.at(i));
	for (int i = pos2; i < parent2Vertexes.size(); ++i)
		child->addVertex(parent2Vertexes.at(i));
	
	return child;
}

Chromosome* GASolver::getRandomChromosomeForCrossover() {
	return population.at(generateNumberInRange(0, population.size() - 1));
}

void GASolver::mutate(Chromosome* chromosome) {
	const int maxMutationLength = 3;

	vector<Vertex*> chromosomeVertexes = chromosome->getVertexes();

	int beginIndex = generateNumberInRange(0, chromosomeVertexes.size() - maxMutationLength - 1);
	if (beginIndex < 0)
		beginIndex = 0;

	int endIndex = beginIndex + generateNumberInRange(1, maxMutationLength);
	if (endIndex > chromosomeVertexes.size() - 1)
		endIndex = chromosomeVertexes.size() - 1;

	Chromosome* subChromosome = new Chromosome;
	Chromosome* deadEndVertexes = new Chromosome;

	getRandomPath(chromosomeVertexes.at(beginIndex), chromosomeVertexes.at(endIndex), subChromosome, deadEndVertexes);
	chromosome->replace(beginIndex, endIndex, subChromosome);

	delete deadEndVertexes;
	delete subChromosome;
}

void GASolver::deleteTheWorstChromosome() {
	int index = 0;
	for (int i = 1; i < population.size(); ++i) {
		if (population.at(i)->getLength() > population.at(index)->getLength())
			index = i;
	}

	delete population.at(index);
	population.erase(population.begin() + index);
}


GASolver::~GASolver() {
	for (auto chromosome : population)
		delete chromosome;
}