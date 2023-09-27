#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/RandomGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1tests
{
	TEST_CLASS(Lab1tests)
	{
	public:

		TEST_METHOD(generate_number_from_range1)
		{
			RandomGenerator test;
			Assert::AreEqual(test.generate_number_from_range(1, 1), 1);
		}

		TEST_METHOD(generate_number_from_range2)
		{
			RandomGenerator test;
			int low_border = 1, top_border = 5;
			int random_number = test.generate_number_from_range(low_border, top_border);
			Assert::IsTrue(random_number >= low_border && random_number <= top_border);
		}
	};
}
