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
		TEST_METHOD(polyphase_merge_sort_test_asc)
		{
			const int AMOUNT_OF_NUMBERS = 10;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";
			string result_file_path = "test_result" + file_extension;

			int* data{ new int[AMOUNT_OF_NUMBERS] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} };


			ArrayReader data_to_sort(data);
			FileSorter sorter(&data_to_sort, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES, result_file_path);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(result_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			remove(result_file_path.c_str());
		}

		TEST_METHOD(polyphase_merge_sort_test_desc)
		{
			const int AMOUNT_OF_NUMBERS = 10;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";
			string result_file_path = "test_result" + file_extension;

			int* data{ new int[AMOUNT_OF_NUMBERS] {10, 9, 8, 7, 6, 5, 4, 3, 2, 1} };


			ArrayReader data_to_sort(data);
			FileSorter sorter(&data_to_sort, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES, result_file_path);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(result_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			remove(result_file_path.c_str());
		}

		TEST_METHOD(polyphase_merge_sort_test_rand)
		{
			const int AMOUNT_OF_NUMBERS = 10;
			const int AMOUNT_OF_SUPPORTING_FILES = 3;
			string file_extension = ".bin";
			string supporting_file_prefix = "test_supporting_";
			string result_file_path = "test_result" + file_extension;

			int* data{ new int[AMOUNT_OF_NUMBERS] {5, 3, 8, 1, 2, 6, 10, 7, 4, 9} };


			ArrayReader data_to_sort(data);
			FileSorter sorter(&data_to_sort, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES, result_file_path);
			sorter.polyphase_merge_sort();

			ifstream file_after_sorting(result_file_path, ios::binary);
			int current_number, previous_number;
			file_after_sorting.read((char*)&current_number, sizeof(current_number));
			while (!file_after_sorting.eof()) {
				previous_number = current_number;
				file_after_sorting.read((char*)&current_number, sizeof(current_number));
				Assert::IsTrue(current_number >= previous_number);
			}
			file_after_sorting.close();

			remove(result_file_path.c_str());
		}
	};
}
