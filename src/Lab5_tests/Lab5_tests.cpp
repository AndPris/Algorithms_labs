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
}
