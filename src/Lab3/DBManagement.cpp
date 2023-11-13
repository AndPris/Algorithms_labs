#include "DBManagement.h"
#define MINIMUM_DEGREE 100;

using namespace Lab3;

DBManagement::DBManagement(string file_path_to_save) {
	InitializeComponent();
	this->minimum_degree = MINIMUM_DEGREE;
	this->file_path_to_save = new string(file_path_to_save);

	string a = *this->file_path_to_save;

	this->tree = new BTree(this->minimum_degree);
	disable_edit_delete_search();
}

Void DBManagement::insertion_btn_Click(Object^ sender, EventArgs^ e) {
	Record rec;
	try {
		rec.key = get_input(key_to_insert);
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
		return;
	}

	strcpy(rec.data, String_to_string(data_to_insert->Text).c_str());

	try {
		tree->insert(rec);
		key_to_insert->Text = "";
		data_to_insert->Text = "";
		display();
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
	}
}
Void DBManagement::deletion_btn_Click(Object^ sender, EventArgs^ e) {
	int key;
	try {
		key = get_input(key_to_delete);
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
		return;
	}

	try {
		tree->remove(key);
		key_to_delete->Text = "";
		remove_row(key);
	}
	catch (string er) {
		MessageBox::Show(string_to_String(er));
	}
}

void DBManagement::display() {
	vector<Record> records;
	tree->traverse(records);

	enable_edit_delete_search();
	int amount_of_iterations = records.size() - data_table->Rows->Count;
	for(int i = 0; i < amount_of_iterations; ++i)
		data_table->Rows->Add();

	for (int i = 0; i < records.size(); ++i) {
		data_table->Rows[i]->Cells[0]->Value = records.at(i).key;
		data_table->Rows[i]->Cells[1]->Value = char_string_into_String(records.at(i).data);
	}

	records.clear();
}
void DBManagement::remove_row(int key) {
	for (int i = 0; i < data_table->Rows->Count; ++i) {
		int row_key = Convert::ToInt16(data_table->Rows[i]->Cells[0]->Value);
		if (row_key == key) {
			data_table->Rows->RemoveAt(i);
			break;
		}
	}

	if (data_table->Rows->Count == 0)
		disable_edit_delete_search();
}
void DBManagement::disable_edit_delete_search() {
	key_to_edit->Enabled = false;
	key_to_delete->Enabled = false;
	key_to_find->Enabled = false;

	new_data->Enabled = false;

	deletion_btn->Enabled = false;
	find_btn->Enabled = false;
	editing_btn->Enabled = false;
}

void DBManagement::enable_edit_delete_search() {
	key_to_edit->Enabled = true;
	key_to_delete->Enabled = true;
	key_to_find->Enabled = true;

	new_data->Enabled = true;

	deletion_btn->Enabled = true;
	find_btn->Enabled = true;
	editing_btn->Enabled = true;
}