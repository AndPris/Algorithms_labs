#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab4/FullGraph.h"
#include "../Lab4/Vertex_Edge_Path.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab4tests
{
	TEST_CLASS(FullGraphTests)
	{
	public:
		
		TEST_METHOD(getAmountOfVertexesTest) {
			int amountOfVertexes = 10;
			FullGraph graph(amountOfVertexes);
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
	};

	TEST_CLASS(EdgeTests)
	{
	private:
		Edge* edge;
		Vertex* vertex1;
		Vertex* vertex2;
		int length;
		float amountOfPheromone;
		float evaporationCoefficient;
	public:
		EdgeTests() {
			int number1 = 1;
			int number2 = 2;
			vertex1 = new Vertex(number1);
			vertex2 = new Vertex(number2);
			length = 10;
			amountOfPheromone = 10;
			evaporationCoefficient = 0.5;
			edge = new Edge(vertex1, vertex2, length, amountOfPheromone, evaporationCoefficient);
		}
		
		TEST_METHOD(getLengthTest) {
			Assert::AreEqual(length, edge->getLength());
		}
		TEST_METHOD(getAmountOfPheromoneTest) {
			Assert::AreEqual(amountOfPheromone, edge->getAmountOfPheromone());
		}
		TEST_METHOD(evaporatePheromoneTest) {
			edge->evaporatePheromone();
			Assert::AreEqual(amountOfPheromone*evaporationCoefficient, edge->getAmountOfPheromone());
		}
		TEST_METHOD(addPheromoneTest) {
			float additionalPheromone = 5;
			edge->addPheromone(5);
			Assert::AreEqual(amountOfPheromone+additionalPheromone, edge->getAmountOfPheromone());
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
			Edge testEdge(vertex1, vertex2, length, amountOfPheromone, evaporationCoefficient);
			Assert::IsTrue(*edge == testEdge);
		}

		TEST_METHOD(nonEqualEdgesComparrisonTest) {
			int number1 = 5;
			int number2 = 6;
			Vertex testVertex1(number1);
			Vertex testVertex2(number2);
			Edge testEdge(&testVertex1, &testVertex2, length, amountOfPheromone, evaporationCoefficient);
			Assert::IsFalse(*edge == testEdge);
		}
		~EdgeTests() {
			delete edge;
			delete vertex1;
			delete vertex2;
		}
	};

	
}
