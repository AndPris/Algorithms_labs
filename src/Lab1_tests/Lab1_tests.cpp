#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/FileCreator.h"
#include "../Lab1/FileSorter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1tests
{
	TEST_CLASS(FileCreatorTest)
	{
	public:

		TEST_METHOD(creatre_initial_file_creation_test)
		{
			string file_path = "creating_test.bin";
			wstring file_path_w = wstring(file_path.begin(), file_path.end());
			const wchar_t* result_path = file_path_w.c_str();
			const int size_of_file_in_mb = 1;

			FileCreator creator(result_path, size_of_file_in_mb);
			creator.create_initial_file();

			ifstream created_file(file_path, ios::binary);
			Assert::IsTrue(created_file.is_open());
			created_file.close();

			remove(file_path.c_str());
		}

		TEST_METHOD(creatre_initial_file_size_test)
		{
			string file_path = "creating_test.bin";
			wstring file_path_w = wstring(file_path.begin(), file_path.end());
			const wchar_t* result_path = file_path_w.c_str();
			const int size_of_file_in_mb = 1;

			FileCreator creator(result_path, size_of_file_in_mb);
			creator.create_initial_file();

			ifstream created_file(file_path, ios::binary);
			created_file.seekg(0, ios::end);

			int file_size = created_file.tellg();
			Assert::AreEqual(file_size, (size_of_file_in_mb * 1024 * 1024));
			
			created_file.close();

			remove(file_path.c_str());
		}
	};

	TEST_CLASS(FileSorterTest)
	{
	public:

		TEST_METHOD(polyphase_merge_sort_test_sorted_asc)
		{
			const int SIZE_OF_FILE_IN_MB = 20;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";

			const wchar_t* initial_file_path = L"test_initial.bin";
			ofstream test_file(initial_file_path, ios::binary);
			for (int i = 0; i < SIZE_OF_FILE_IN_MB * 1024 * 1024 / sizeof(int); ++i)
				test_file.write((char*)&i, sizeof(i));
			test_file.close();


			FileSorter sorter(initial_file_path, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(initial_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			_wremove(initial_file_path);
		}

		TEST_METHOD(polyphase_merge_sort_test_sorted_desc)
		{
			const int SIZE_OF_FILE_IN_MB = 20;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";

			const wchar_t* initial_file_path = L"test_initial.bin";
			ofstream test_file(initial_file_path, ios::binary);
			for (int i = SIZE_OF_FILE_IN_MB * 1024 * 1024 / sizeof(int)-1; i >= 0; --i)
				test_file.write((char*)&i, sizeof(i));
			test_file.close();


			FileSorter sorter(initial_file_path, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(initial_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			_wremove(initial_file_path);
		}

		TEST_METHOD(polyphase_merge_sort_test_sorted_rand)
		{
			srand(time(nullptr));
			const int SIZE_OF_FILE_IN_MB = 20;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";

			const wchar_t* initial_file_path = L"test_initial.bin";
			ofstream test_file(initial_file_path, ios::binary);
			for (int i = 0; i < SIZE_OF_FILE_IN_MB * 1024 * 1024 / sizeof(int); ++i) {
				int random_number = rand();
				test_file.write((char*)&random_number, sizeof(random_number));
			}
			test_file.close();


			FileSorter sorter(initial_file_path, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(initial_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			_wremove(initial_file_path);
		}
	};
}
