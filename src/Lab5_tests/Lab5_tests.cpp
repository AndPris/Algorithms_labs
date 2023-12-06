#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab5/chromosome.h"
#include "../Lab5/vertex_edge.h"
#include "../Lab5/graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab5tests
{
	TEST_CLASS(GraphTests)
	{
	public:

		TEST_METHOD(getAmountOfVertexesTest) {
			int amountOfVertexes = 10;
			Graph graph(amountOfVertexes);
			Assert::AreEqual(amountOfVertexes, graph.getAmountOfVertexes());
		}
	};

	TEST_CLASS(VertexTests)
	{
	public:

		TEST_METHOD(getNumberTest) {
			int number = 1;
			Vertex vertex(number);
			Assert::AreEqual(number, vertex.getNumber());
		}

		TEST_METHOD(equalVertexesComparrisonTest) {
			int number = 1;
			Vertex vertex1(number);
			Vertex vertex2(number);
			Assert::IsTrue(vertex1 == vertex2);
		}

		TEST_METHOD(nonEqualVertexesComparrisonTest) {
			int number1 = 1;
			int number2 = 2;
			Vertex vertex1(number1);
			Vertex vertex2(number2);
			Assert::IsFalse(vertex1 == vertex2);
		}

		TEST_METHOD(getConnectionEdgeTest1) {
			int number1 = 1;
			int number2 = 2;
			Vertex vertex1(number1);
			Vertex vertex2(number2);

			Edge edge = Edge(&vertex1, &vertex2, 0);
			vertex1.addIncidentEdge(&edge);
			vertex2.addIncidentEdge(&edge);

			Assert::IsTrue(vertex1.getConnectingEdge(&vertex2) == &edge);
		}
		TEST_METHOD(getConnectionEdgeTest2) {
			int number1 = 1;
			int number2 = 2;
			Vertex vertex1(number1);
			Vertex vertex2(number2);

			Edge edge = Edge(&vertex1, &vertex2, 0);
			vertex1.addIncidentEdge(&edge);
			vertex2.addIncidentEdge(&edge);

			Assert::IsTrue(vertex2.getConnectingEdge(&vertex1) == &edge);
		}
	};

	TEST_CLASS(EdgeTests)
	{
	private:
		Edge* edge;
		Vertex* vertex1;
		Vertex* vertex2;
		int length;
	public:
		EdgeTests() {
			int number1 = 1;
			int number2 = 2;
			vertex1 = new Vertex(number1);
			vertex2 = new Vertex(number2);
			length = 10;
			edge = new Edge(vertex1, vertex2, length);
		}

		TEST_METHOD(getLengthTest) {
			Assert::AreEqual(length, edge->getLength());
		}
		TEST_METHOD(containsExistingTest) {
			Assert::IsTrue(edge->contains(vertex1));
		}
		TEST_METHOD(containsNonExistingTest) {
			Vertex vertex(5);
			Assert::IsFalse(edge->contains(&vertex));
		}
		TEST_METHOD(getConnectedVertexesTest) {
			vector<Vertex*> connectedVertexes = edge->getConnectedVertexes();
			Assert::IsTrue(vertex1 == connectedVertexes.at(0));
			Assert::IsTrue(vertex2 == connectedVertexes.at(1));
		}

		TEST_METHOD(equalEdgesComparrisonTest) {
			Edge testEdge(vertex1, vertex2, length);
			Assert::IsTrue(*edge == testEdge);
		}

		TEST_METHOD(nonEqualEdgesComparrisonTest) {
			int number1 = 5;
			int number2 = 6;
			Vertex testVertex1(number1);
			Vertex testVertex2(number2);
			Edge testEdge(&testVertex1, &testVertex2, length);
			Assert::IsFalse(*edge == testEdge);
		}
		~EdgeTests() {
			delete edge;
			delete vertex1;
			delete vertex2;
		}
	};

	TEST_CLASS(ChromosomeTests)
	{
	private:
		Edge *edge1, *edge2;
		Vertex *vertex1, *vertex2, *vertex3;
		int length1, length2;
		Chromosome* chromosome;
	public:
		ChromosomeTests() {
			chromosome = new Chromosome;

			int number1 = 1;
			int number2 = 2;
			int number3 = 3;

			length1 = 5;
			length2 = 10;

			vertex1 = new Vertex(number1);
			vertex2 = new Vertex(number2);
			vertex3 = new Vertex(number3);

			edge1 = new Edge(vertex1, vertex2, length1);
			edge2 = new Edge(vertex2, vertex3, length2);

			vertex1->addIncidentEdge(edge1);
			vertex2->addIncidentEdge(edge1);
			vertex2->addIncidentEdge(edge2);
			vertex3->addIncidentEdge(edge2);

			chromosome->addVertex(vertex1);
			chromosome->addVertex(vertex2);
			chromosome->addVertex(vertex3);
		}

		TEST_METHOD(getLengthTest) {
			Assert::AreEqual(length1+length2, chromosome->getLength());
		}
		TEST_METHOD(containsExistingTest) {
			Assert::IsTrue(chromosome->contains(vertex1));
		}
		TEST_METHOD(containsNonExistingTest) {
			Vertex vertex(5);
			Assert::IsFalse(chromosome->contains(&vertex));
		}
		TEST_METHOD(getVertexesTest) {
			vector<Vertex*> connectedVertexes = chromosome->getVertexes();
			Assert::IsTrue(vertex1 == connectedVertexes.at(0));
			Assert::IsTrue(vertex2 == connectedVertexes.at(1));
			Assert::IsTrue(vertex3 == connectedVertexes.at(2));
		}

		TEST_METHOD(equalChromosomeComparrisonTest) {
			Chromosome testChromosome;
			testChromosome.addVertex(vertex1);
			testChromosome.addVertex(vertex2);
			testChromosome.addVertex(vertex3);
			Assert::IsTrue(*chromosome == testChromosome);
		}

		TEST_METHOD(nonEqualChromosomeComparrisonTest1) {
			Chromosome testChromosome;
			testChromosome.addVertex(vertex1);
			testChromosome.addVertex(vertex2);
			Assert::IsFalse(*chromosome == testChromosome);
		}

		TEST_METHOD(nonEqualChromosomeComparrisonTest2) {
			Chromosome testChromosome;
			Vertex vertex(5);
			testChromosome.addVertex(vertex1);
			testChromosome.addVertex(vertex2);
			testChromosome.addVertex(&vertex);
			Assert::IsFalse(*chromosome == testChromosome);
		}

		TEST_METHOD(delteLastVertexTest) {
			chromosome->deleteLastVertex();
			Assert::IsFalse(chromosome->contains(vertex3));
		}

		TEST_METHOD(findPositionsOfIntersectionTest1) {
			Chromosome testChromosome;
			Vertex testVertex1(5);
			Vertex testVertex2(10);
			testChromosome.addVertex(&testVertex1);
			testChromosome.addVertex(vertex2);
			testChromosome.addVertex(&testVertex2);

			vector<int> intersectionIndexes = chromosome->findPositionsOfIntersection(&testChromosome);

			Assert::AreEqual(1, intersectionIndexes.at(0));
			Assert::AreEqual(1, intersectionIndexes.at(1));
		}

		TEST_METHOD(findPositionsOfIntersectionTest2) {
			Chromosome testChromosome;
			Vertex testVertex1(5);
			Vertex testVertex2(10);
			testChromosome.addVertex(&testVertex1);
			testChromosome.addVertex(&testVertex2);

			vector<int> intersectionIndexes = chromosome->findPositionsOfIntersection(&testChromosome);

			Assert::IsTrue(intersectionIndexes.empty());
		}
		~ChromosomeTests() {
			delete edge1;
			delete edge2;

			delete vertex1;
			delete vertex2;
			delete vertex3;

			delete chromosome;
		}
	};
}
