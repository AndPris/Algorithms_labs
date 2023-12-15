#include "PresidentForm.h"
#include <stdlib.h>
#include <ctime>

using namespace Lab6;


PresidentForm::PresidentForm(void) {
	InitializeComponent();
	srand(time(nullptr));
	president = new PresidentI;
	president->displayAllCards(humanCards);
}

PresidentForm::~PresidentForm() {
	if (components)
		delete components;
	
	delete president;
}