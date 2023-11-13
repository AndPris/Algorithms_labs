#include "DBManagement.h"
#define MINIMUM_DEGREE 100;

using namespace Lab3;

DBManagement::DBManagement(string file_path_to_save) {
	InitializeComponent();
	this->minimum_degree = MINIMUM_DEGREE;
	this->file_path_to_save = new string(file_path_to_save);

	string a = *this->file_path_to_save;

	this->tree = new BTree(this->minimum_degree);
}

Void DBManagement::insertion_btn_Click(Object^ sender, EventArgs^ e) {
	Record rec;
	rec.key = Convert::ToInt16(key_to_insert->Text);
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

void DBManagement::display() {
	vector<Record> records;
	tree->traverse(records);

	for(int i = 0; i < records.size() - data_table->Rows->Count; ++i)
		data_table->Rows->Add();

	for (int i = 0; i < records.size(); ++i) {
		data_table->Rows[i]->Cells[0]->Value = records.at(i).key;
		data_table->Rows[i]->Cells[1]->Value = char_string_into_String(records.at(i).data);
	}

	records.clear();
}