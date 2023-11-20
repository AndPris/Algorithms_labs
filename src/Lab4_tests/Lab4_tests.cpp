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
}
