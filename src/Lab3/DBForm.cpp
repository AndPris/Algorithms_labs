#include "DBForm.h"

using namespace Lab3;
using namespace std;

Void DBForm::DB_creation_btn_Click(Object^ sender, EventArgs^ e) {
	string extension = ".mdb";

	SaveFileDialog^ file_dialog = gcnew SaveFileDialog();
	file_dialog->Filter = "My data base file | *.mdb";
	file_dialog->Title = "Create data base";
	file_dialog->InitialDirectory = Application::StartupPath;

	if (file_dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		string file_name = String_to_string(file_dialog->FileName);
		validate_file_path(file_name, extension);

		DBManagement^ db_management_window = gcnew DBManagement(file_name);
		db_management_window->Show();
	}
}