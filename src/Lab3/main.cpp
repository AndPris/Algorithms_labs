#include "DBForm.h"

using namespace System;
using namespace Windows::Forms;
using namespace Lab3;

[STAThreadAttribute]
int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	DBForm^ welcome_form = gcnew DBForm;
	Application::Run(welcome_form);

	return 0;
}