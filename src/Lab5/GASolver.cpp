#include "GASolver.h"

GASolver::GASolver(Graph* graph, Vertex* source, Vertex* destination) {
	this->populationSize = POPULATION_SIZE;
	this->graphToSolve = graph;
	this->source = source;
	this->destination = destination;

	createInitialPopulation();

	/*cout << "Initial:" << endl;
	for (auto elem : population)
		elem->display();*/

	findCurrentBestChromosome();

	cout << "Best chromosome:" << endl;
	currentBestChromosome->display();
}

void GASolver::createInitialPopulation() {
	for (int i = 0; i < populationSize; ++i) {
		Chromosome* path = new Chromosome;
		Vertex* startVertex = source;
		Vertex* endVertex = destination;
		getRandomPath(source, destination, path);

		//TODO:: remove
		path->display();

		population.push_back(path);
	}
}

void GASolver::findCurrentBestChromosome() {
	currentBestChromosome = population.at(0);

	for (int i = 1; i < population.size(); ++i) {
		if (population.at(i)->getLength() < currentBestChromosome->getLength())
			currentBestChromosome = population.at(i);
	}
}

bool GASolver::getRandomPath(Vertex* startVertex, Vertex* endVertex, Chromosome*& path) {
	if (startVertex == endVertex) {
		path->addVertex(startVertex);
		return true;
	}
	
	path->addVertex(startVertex);

	vector<Vertex*> possibleNextVertexes = getPossibleNextVertexes(startVertex, path);

	if (possibleNextVertexes.empty()) {
		path->deleteLastVertex();
		return false;
	}

	random_shuffle(possibleNextVertexes.begin(), possibleNextVertexes.end());

	for (auto vertex : possibleNextVertexes) {
		if (getRandomPath(vertex, endVertex, path))
			return true;
	}

	path->deleteLastVertex();
	return false;
}

vector<Vertex*> GASolver::getPossibleNextVertexes(Vertex* currentVertex, Chromosome* visitedVertexes) {
	vector<Vertex*> possibleNextVertexes;

	for (auto edge : currentVertex->getIncidentEdges()) {
		Vertex* nextVertex;
		vector<Vertex*> connectedVertexes = edge->getConnectedVertexes();

		if (currentVertex == connectedVertexes.at(0))
			nextVertex = connectedVertexes.at(1);
		else
			nextVertex = connectedVertexes.at(0);

		if (!visitedVertexes->contains(nextVertex))
			possibleNextVertexes.push_back(nextVertex);
	}

	return possibleNextVertexes;
}

void GASolver::solve() {
	for (int i = 0; i < 10; ++i) {
		Chromosome* randomChromosomeForCrossover = getRandomChromosomeForCrossover();
		Chromosome* childChromosome = crossover(currentBestChromosome, randomChromosomeForCrossover);


	}
}

Chromosome* GASolver::crossover(Chromosome* parent1, Chromosome* parent2) {
	int pos1 = parent1->findPositionOfIntersection(parent2);
	int pos2 = parent2->findPositionOfIntersection(parent1);

	vector<Vertex*> parent1Vertexes = parent1->getVertexes();
	vector<Vertex*> parent2Vertexes = parent2->getVertexes();

	Chromosome* child = new Chromosome;

	for (int i = 0; i < pos1; ++i)
		child->addVertex(parent1Vertexes.at(i));
	for (int i = pos2; i < parent2Vertexes.size(); ++i)
		child->addVertex(parent2Vertexes.at(i));
	
	cout << "Parent1:" << endl;
	parent1->display();
	cout << "Parent2:" << endl;
	parent2->display();
	cout << "Child:" << endl;
	child->display();
	cout << "------------------------------" << endl;

	return child;
}

Chromosome* GASolver::getRandomChromosomeForCrossover() {
	int index = 0;

	do {
		index = generateNumberInRange(0, population.size() - 1);
	} while (population.at(index)->findPositionOfIntersection(currentBestChromosome) == -1);

	return population.at(index);
}


GASolver::~GASolver() {
	for (auto chromosome : population)
		delete chromosome;
}