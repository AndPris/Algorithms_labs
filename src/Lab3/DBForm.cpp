#include "DBForm.h"

using namespace Lab3;
using namespace std;

Void DBForm::DB_creation_btn_Click(Object^ sender, EventArgs^ e) {
	SaveFileDialog^ file_dialog = gcnew SaveFileDialog();
	file_dialog->Filter = "My data base file | *.mdb";
	file_dialog->Title = "Create data base";
	file_dialog->InitialDirectory = Application::StartupPath;

	if (file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		open_db_management_window(file_dialog->FileName, false);
}

Void DBForm::DB_opening_btn_Click(Object^ sender, EventArgs^ e) {
	OpenFileDialog^ file_dialog = gcnew OpenFileDialog();
	file_dialog->Filter = "My data base file | *.mdb";
	file_dialog->Title = "Open data base file";
	file_dialog->InitialDirectory = Application::StartupPath;

	if (file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		open_db_management_window(file_dialog->FileName, true);
}

void DBForm::open_db_management_window(String^ file_path, bool open) {
	string extension = ".mdb";

	string file_name = String_to_string(file_path);
	validate_file_path(file_name, extension);

	DBManagement^ db_management_window = gcnew DBManagement(file_name, open);
	db_management_window->Show();
}
