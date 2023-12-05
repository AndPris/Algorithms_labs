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
		//path->display();

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

	vector<Vertex*> possibleNextVertexes = getPossibleNextVertexes(startVertex, endVertex, path);

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

vector<Vertex*> GASolver::getPossibleNextVertexes(Vertex* currentVertex, Vertex* endVertex, Chromosome* visitedVertexes) {
	vector<Vertex*> possibleNextVertexes;

	for (auto edge : currentVertex->getIncidentEdges()) {
		Vertex* nextVertex;
		vector<Vertex*> connectedVertexes = edge->getConnectedVertexes();

		if (currentVertex == connectedVertexes.at(0))
			nextVertex = connectedVertexes.at(1);
		else
			nextVertex = connectedVertexes.at(0);

		if (!visitedVertexes->contains(nextVertex) && nextVertex->getNumber() > currentVertex->getNumber() && nextVertex->getNumber() <= endVertex->getNumber())
			possibleNextVertexes.push_back(nextVertex);
	}

	return possibleNextVertexes;
}

void GASolver::solve() {
	int iterationsWithoutImprovement = 0;

	/*for (int i = 0; i < AMOUNT_OF_ITERATIONS; ++i) {*/
	while(iterationsWithoutImprovement < 100) {
		++iterationsWithoutImprovement;

		Chromosome* randomChromosomeForCrossover = getRandomChromosomeForCrossover();
		Chromosome* childChromosome = crossover(currentBestChromosome, randomChromosomeForCrossover);
		/*cout << "Child:" << endl;
		childChromosome->display();
		cout << "childChromosome Length: " << childChromosome->getLength() << endl;*/

		mutate(childChromosome);
		/*cout << "Mutation:" << endl;
		childChromosome->display();
		cout << "Mutation Length: " << childChromosome->getLength() << endl;*/


		population.push_back(childChromosome);

		if (childChromosome->getLength() <= currentBestChromosome->getLength()) {
			currentBestChromosome = childChromosome;
			iterationsWithoutImprovement = 0;
		}
		
		deleteTheWorstChromosome();
		cout << "Best chromosome Length: " << currentBestChromosome->getLength() << endl;
		cout << "---------------------------" << endl;
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

	return child;
}

Chromosome* GASolver::getRandomChromosomeForCrossover() {
	int index = 0;

	do {
		index = generateNumberInRange(0, population.size() - 1);
	} while (population.at(index)->findPositionOfIntersection(currentBestChromosome) == -1);

	return population.at(index);
}

void GASolver::mutate(Chromosome* chromosome) {
	const int maxMutationLength = 3;

	vector<Vertex*> chromosomeVertexes = chromosome->getVertexes();

	int beginIndex = generateNumberInRange(0, chromosomeVertexes.size() - maxMutationLength -1);
	int endIndex = beginIndex + generateNumberInRange(1, maxMutationLength);

	//cout << "Begin: " << beginIndex << ", end:" << endIndex << endl;
	Chromosome* subChromosome = new Chromosome;
	getRandomPath(chromosomeVertexes.at(beginIndex), chromosomeVertexes.at(endIndex), subChromosome);
	chromosome->replace(beginIndex, endIndex, subChromosome);

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