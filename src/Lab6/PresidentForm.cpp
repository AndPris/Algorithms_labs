#include "PresidentForm.h"
#include <stdlib.h>
#include <ctime>

using namespace Lab6;


PresidentForm::PresidentForm(void) {
	InitializeComponent();

	const int maxAmountOfCards = 13;
	humanCards->Height = CARD_HEIGHT + 60;
	humanCards->Width = CARD_WIDTH*maxAmountOfCards;
	humanCards->Location = Point((this->Width - humanCards->Width) / 2, this->Height - humanCards->Height);

	srand(time(nullptr));
	president = new PresidentI;
	president->displayAllCards(humanCards);
}

PresidentForm::~PresidentForm() {
	if (components)
		delete components;
	
	delete president;
}