#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3_code/B_Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3tests
{
	TEST_CLASS(BTree_tests)
	{
		BTree create_BTree(int amount_of_records, int minimal_degree) {
			BTree tree(minimal_degree);
			for (int i = 0; i < amount_of_records; ++i) {
				Record record;
				record.key = i + 1;
				strcpy_s(record.data, "data");
				strcat_s(record.data, (to_string(i + 1)).c_str());
				tree.insert(record);
			}
			return tree;
		}

	public:
		TEST_METHOD(search_present_one_node) {
			BTree tree = create_BTree(6, 3);
			int key_to_search = 1;

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_first) {
			BTree tree = create_BTree(6, 3);
			int key_to_search = 1;


			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_median) {
			BTree tree = create_BTree(6, 3);
			int key_to_search = 3;

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_present_two_nodes_last) {
			BTree tree = create_BTree(6, 3);
			int key_to_search = 6;

			Record result = tree.search(key_to_search);

			Assert::AreEqual(result.key, key_to_search);
			char expected_data[250] = "data";
			strcat_s(expected_data, (to_string(key_to_search)).c_str());
			Assert::AreEqual(result.data, expected_data);
		}
		TEST_METHOD(search_absent) {
			BTree tree = create_BTree(6, 3);
			int key_to_search = 7;

			auto func = [&tree, key_to_search] { tree.search(key_to_search); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(insert_already_present) {
			BTree tree = create_BTree(6, 3);
			int key_to_insert = 3;

			Record record = { key_to_insert, "test data" };
			auto func = [&tree, &record] { tree.insert(record); };
			Assert::ExpectException<const char*>(func);
		}
		TEST_METHOD(delete_absent) {
			BTree tree = create_BTree(6, 3);
			int key_to_delete = 7;

			auto func = [&tree, key_to_delete] { tree.remove(key_to_delete); };
			Assert::ExpectException<string>(func);
		}

		TEST_METHOD(delete_present_first) {
			BTree tree = create_BTree(6, 3);
			int key_to_delete = 1;

			tree.remove(key_to_delete);

			auto func = [&tree, key_to_delete] { tree.search(key_to_delete); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(delete_present_median) {
			BTree tree = create_BTree(6, 3);
			int key_to_delete = 3;

			tree.remove(key_to_delete);

			auto func = [&tree, key_to_delete] { tree.search(key_to_delete); };
			Assert::ExpectException<const char*>(func);
		}

		TEST_METHOD(edit_present_first) {
			BTree tree = create_BTree(6, 3);
			int key_to_edit = 1;
			char* new_data = "new data";

			tree.edit(key_to_edit, new_data);

			Record result = tree.search(key_to_edit);

			Assert::AreEqual(result.key, key_to_edit);
			Assert::AreEqual(result.data, new_data);
		}
		TEST_METHOD(edit_present_median) {
			BTree tree = create_BTree(6, 3);
			int key_to_edit = 3;

			char* new_data = "new data";

			tree.edit(key_to_edit, new_data);

			Record result = tree.search(key_to_edit);

			Assert::AreEqual(result.key, key_to_edit);
			Assert::AreEqual(result.data, new_data);
		}
		TEST_METHOD(edit_present_last) {
			BTree tree = create_BTree(6, 3);
			int key_to_edit = 6;

			char* new_data = "new data";

			tree.edit(key_to_edit, new_data);

			Record result = tree.search(key_to_edit);

			Assert::AreEqual(result.key, key_to_edit);
			Assert::AreEqual(result.data, new_data);
		}
		TEST_METHOD(edit_absent) {
			BTree tree = create_BTree(6, 3);
			int key_to_edit = 7;
			char* new_data = "new data";

			auto func = [&tree, key_to_edit, new_data] { tree.edit(key_to_edit, new_data); };
			Assert::ExpectException<const char*>(func);
		}
	};
}
