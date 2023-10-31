#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2/PuzzleSolver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2tests
{
	TEST_CLASS(PuzzleSolverTest)
	{
	private:
		bool are_equal_matrixes(int** first, int** second, int size) {
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					if (first[i][j] != second[i][j])
						return false;
				}
			}
			return true;
		}

	public:
		
		TEST_METHOD(LDFS_test)
		{
			const int PUZZLE_SIZE = 3;
			const int LIMIT = 26;
			int** puzzle{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {1, 0, 2},
							new int [PUZZLE_SIZE] {3, 4, 5},
							new int [PUZZLE_SIZE] {6, 7, 8}} };
			int** goal{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {0, 1, 2},
							new int [PUZZLE_SIZE] {3, 4, 5},
							new int [PUZZLE_SIZE] {6, 7, 8}} };

			PuzzleSolver solver;

			int** result = solver.LDFS_solve(puzzle, PUZZLE_SIZE, LIMIT);

			Assert::IsTrue(are_equal_matrixes(result, goal, PUZZLE_SIZE));
		}

		TEST_METHOD(A_Star_test_1)
		{
			const int PUZZLE_SIZE = 3;
			int** puzzle{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {1, 0, 2},
							new int [PUZZLE_SIZE] {3, 4, 5},
							new int [PUZZLE_SIZE] {6, 7, 8}} };
			int** goal{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {0, 1, 2},
							new int [PUZZLE_SIZE] {3, 4, 5},
							new int [PUZZLE_SIZE] {6, 7, 8}} };
			PuzzleSolver solver;

			int** result = solver.A_star(puzzle, PUZZLE_SIZE);

			Assert::IsTrue(are_equal_matrixes(result, goal, PUZZLE_SIZE));
		}
		TEST_METHOD(A_Star_test_2)
		{
			const int PUZZLE_SIZE = 3;
			int** puzzle{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {6, 1, 7},
							new int [PUZZLE_SIZE] {4, 5, 3},
							new int [PUZZLE_SIZE] {2, 0, 8}} };
			int** goal{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {0, 1, 2},
							new int [PUZZLE_SIZE] {3, 4, 5},
							new int [PUZZLE_SIZE] {6, 7, 8}} };

			PuzzleSolver solver;

			int** result = solver.A_star(puzzle, PUZZLE_SIZE);

			Assert::IsTrue(are_equal_matrixes(result, goal, PUZZLE_SIZE));
		}
		TEST_METHOD(A_Star_test_invalid)
		{
			const int PUZZLE_SIZE = 3;
			int** puzzle{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {7, 3, 1},
							new int [PUZZLE_SIZE] {5, 2, 6},
							new int [PUZZLE_SIZE] {4, 0, 8}} };

			PuzzleSolver solver;
			auto func = [&solver, &puzzle, &PUZZLE_SIZE] { solver.A_star(puzzle, PUZZLE_SIZE); };
			Assert::ExpectException<const char*>(func);
		}
		TEST_METHOD(LDFS_test_invalid)
		{
			const int PUZZLE_SIZE = 3;
			const int LIMIT = 26;
			int** puzzle{ new int* [PUZZLE_SIZE] {
							new int [PUZZLE_SIZE] {7, 3, 1},
							new int [PUZZLE_SIZE] {5, 2, 6},
							new int [PUZZLE_SIZE] {4, 0, 8}} };

			PuzzleSolver solver;
			auto func = [&solver, &puzzle, &PUZZLE_SIZE, &LIMIT] { solver.LDFS_solve(puzzle, PUZZLE_SIZE, LIMIT); };
			Assert::ExpectException<const char*>(func);
		}
	};
}
