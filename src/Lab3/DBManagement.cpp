#include "DBManagement.h"
#define MINIMUM_DEGREE 100;

using namespace Lab3;

DBManagement::DBManagement(string file_path_to_save, bool open) {
	InitializeComponent();
	this->minimum_degree = MINIMUM_DEGREE;
	this->file_path_to_save = new string(file_path_to_save);

	string a = *this->file_path_to_save;

	this->tree = new BTree(this->minimum_degree);

	if (!open) {
		disable_edit_delete_search();
		return;
	}

	ifstream file(file_path_to_save, ios::binary);

	if (!file) {
		MessageBox::Show("Can't open file");
		return;
	}

	if (is_empty_file(file)) {
		disable_edit_delete_search();
		return;
	}

	tree->open(file);
	display();
	file.close();
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
Void DBManagement::editing_btn_Click(Object^ sender, EventArgs^ e) {
	Record new_record;
	try {
		new_record.key = get_input(key_to_edit);
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
		return;
	}

	strcpy(new_record.data, String_to_string(new_data->Text).c_str());

	try {
		tree->edit(new_record.key, new_record.data);
		key_to_edit->Text = "";
		new_data->Text = "";
		display();
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
	}
}
Void DBManagement::find_btn_Click(Object^ sender, EventArgs^ e) {
	int key;
	try {
		key = get_input(key_to_find);
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
		return;
	}

	try {
		int amount_of_conmarisons = 0;
		Record rec = tree->search(key, amount_of_conmarisons);
		String^ message = "Key: " + Convert::ToString(key) + ", Data: " + char_string_into_String(rec.data) + ", Comparisons: " + Convert::ToString(amount_of_conmarisons);
		MessageBox::Show(message);
		key_to_find->Text = "";
	}
	catch (const char* er) {
		MessageBox::Show(char_string_into_String(er));
	}
}

void DBManagement::display() {
	vector<Record> records;
	tree->traverse(records);

	if(!records.empty())
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
void DBManagement::edit_row(int key, char* data) {
	for (int i = 0; i < data_table->Rows->Count; ++i) {
		int row_key = Convert::ToInt16(data_table->Rows[i]->Cells[0]->Value);
		if (row_key == key) {
			data_table->Rows[i]->Cells[1]->Value = char_string_into_String(data);
			break;
		}
	}
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

DBManagement::~DBManagement() {
	if (components)
	{
		delete components;
	}

	ofstream file_to_save(*file_path_to_save, ios::binary);
	if(!file_to_save)
		MessageBox::Show("Can't save tree");
	else
		tree->save(file_to_save);
	file_to_save.close();

	delete tree;
	delete file_path_to_save;
}