#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab4/FullGraph.h"
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
}
