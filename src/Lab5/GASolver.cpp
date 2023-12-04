#include "GASolver.h"

GASolver::GASolver(Graph* graph, Vertex* source, Vertex* destination) {
	this->populationSize = POPULATION_SIZE;
	this->graphToSolve = graph;
	this->source = source;
	this->destination = destination;

	createInitialPopulation();
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

	if (possibleNextVertexes.empty())
		return false;

	Vertex* nextVertex = possibleNextVertexes.at(generateNumberInRange(0, possibleNextVertexes.size() - 1));
	if (getRandomPath(nextVertex, endVertex, path))
		return true;

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

GASolver::~GASolver() {
	for (auto chromosome : population)
		delete chromosome;
}