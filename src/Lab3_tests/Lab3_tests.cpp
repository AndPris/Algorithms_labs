#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3_code/B_Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3tests
{
	TEST_CLASS(BTree_search_insert)
	{
	public:
		TEST_METHOD(search_present_one_node) {
			int amount_of_records = 3;
			int key_to_search = 1;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_first) {
			int amount_of_records = 6;
			int key_to_search = 1;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_median) {
			int amount_of_records = 6;
			int key_to_search = 3;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_last) {
			int amount_of_records = 6;
			int key_to_search = 6;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_absent) {
			int amount_of_records = 6;
			int key_to_search = 7;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			auto func = [&tree, key_to_search] { tree.search(key_to_search); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(insert_already_present) {
			int key_to_insert = 3;
			int amount_of_records = 6;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			Record record = { key_to_insert, "test data" };
			auto func = [&tree, &record] { tree.insert(record); };
			Assert::ExpectException<const char*>(func);
		}
	};


	TEST_CLASS(BTree_delete)
	{
	public:

		TEST_METHOD(delete_absent) {
			int amount_of_records = 6;
			int key_to_delete = 7;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			auto func = [&tree, key_to_delete] { tree.remove(key_to_delete); };
			Assert::ExpectException<string>(func);
		}

		TEST_METHOD(delete_present_first) {
			int amount_of_records = 6;
			int key_to_delete = 1;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			tree.remove(key_to_delete);

			auto func = [&tree, key_to_delete] { tree.search(key_to_delete); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(delete_present_median) {
			int amount_of_records = 6;
			int key_to_delete = 3;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			tree.remove(key_to_delete);

			auto func = [&tree, key_to_delete] { tree.search(key_to_delete); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(delete_present_last) {
			int amount_of_records = 6;
			int key_to_delete = 6;
			BTree tree(3);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}

			tree.remove(key_to_delete);

			auto func = [&tree, key_to_delete] { tree.search(key_to_delete); };
			Assert::ExpectException<const char*>(func);
		}
	};
}
