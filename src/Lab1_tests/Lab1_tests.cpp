#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/FileCreator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1tests
{
	TEST_CLASS(FileCreatorTest)
	{
	public:

		TEST_METHOD(creatre_initial_file)
		{
			string file_path = "creating_test.bin";
			wstring file_path_w = wstring(file_path.begin(), file_path.end());
			const wchar_t* result_path = file_path_w.c_str();
			const int size_of_file_in_mb = 1;


			FileCreator creator(result_path, size_of_file_in_mb);
			creator.create_initial_file();

			ifstream created_file(file_path, ios::binary);
			Assert::IsTrue(created_file.is_open());

			created_file.seekg(0, ios::end);
			int file_size = created_file.tellg();
			Assert::AreEqual(file_size, (size_of_file_in_mb * 1024 * 1024));
			created_file.close();

			remove(file_path.c_str());
		}
	};
}
