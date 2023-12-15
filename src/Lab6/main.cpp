#include "PresidentForm.h"

using namespace System;
using namespace Windows::Forms;
using namespace Lab6;

[STAThreadAttribute]
int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	PresidentForm^ mainForm = gcnew PresidentForm;
	Application::Run(mainForm);

	return 0;
}