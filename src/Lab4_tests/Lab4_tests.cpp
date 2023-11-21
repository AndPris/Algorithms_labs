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

	TEST_CLASS(PathTests) {
		Path* path;
		Vertex* vertex1, * vertex2, * vertex3;
		int length, amountOfEdges;
		Edge* edge1, * edge2;
	public:
		PathTests() {
			path = new Path();
			int number1 = 1, number2 = 2, number3 = 3;
			vertex1 = new Vertex(number1);
			vertex2 = new Vertex(number2);
			vertex3 = new Vertex(number3);

			int length1 = 10, length2 = 15;
			length = length1 + length2;

			edge1 = new Edge(vertex1, vertex2, length1, 0, 0);
			edge2 = new Edge(vertex2, vertex3, length2, 0, 0);

			path->addEdge(edge1);
			path->addEdge(edge2);

			amountOfEdges = 2;
		}

		TEST_METHOD(getAmountOfEdgesTest) {
			Assert::AreEqual(amountOfEdges, path->getAmountOfEdges());
		}
		TEST_METHOD(getLengthTest) {
			Assert::AreEqual(length, path->getLength());
		}
		TEST_METHOD(clearAmountOfEdgesTest) {
			path->clear();
			Assert::AreEqual(0, path->getAmountOfEdges());
		}
		TEST_METHOD(clearLengthTest) {
			path->clear();
			Assert::AreEqual(0, path->getLength());
		}
		TEST_METHOD(containsExistingVertexesTest) {
			vector<Vertex*> vertexes;
			vertexes.push_back(vertex1);
			vertexes.push_back(vertex2);

			Assert::IsTrue(path->containsVertexes(vertexes));
		}
		TEST_METHOD(containsNonExistingVertexesTest) {
			vector<Vertex*> vertexes;
			Vertex testVertex(7);
			vertexes.push_back(vertex1);
			vertexes.push_back(&testVertex);

			Assert::IsFalse(path->containsVertexes(vertexes));
		}
		TEST_METHOD(comparisonWithLongerTest) {
			Edge testEdge(vertex1, vertex2, length + 10, 0, 0);
			Path testPath;
			testPath.addEdge(&testEdge);

			Assert::IsTrue(*path < testPath);
		}
		TEST_METHOD(comparisonWithShorterTest) {
			Edge testEdge(vertex1, vertex2, length - 10, 0, 0);
			Path testPath;
			testPath.addEdge(&testEdge);

			Assert::IsFalse(*path < testPath);
		}
		~PathTests() {
			delete path;
			delete vertex1;
			delete vertex2;
			delete vertex3;
			delete edge1;
			delete edge2;
		}
	};
}
