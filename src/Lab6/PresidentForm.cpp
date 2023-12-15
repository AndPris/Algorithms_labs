#include "PresidentForm.h"
#include <stdlib.h>
#include <ctime>

using namespace Lab6;


PresidentForm::PresidentForm(void) {
	InitializeComponent();

	const int maxAmountOfCards = 13;
	int maxWidth = CARD_WIDTH * maxAmountOfCards;
	int maxHeight = CARD_HEIGHT;

	humanCards->Height = maxHeight+60;
	humanCards->Width = maxWidth;
	humanCards->Location = Point((this->Width - humanCards->Width) / 2, this->Height - humanCards->Height);

	AI1Cards->Height = maxWidth/2+CARD_WIDTH;
	AI1Cards->Width = maxHeight*2;
	AI1Cards->Location = Point(0, (this->Height - AI1Cards->Height)/2);

	AI2Cards->Height = maxHeight;
	AI2Cards->Width = maxWidth;
	AI2Cards->Location = Point((this->Width - AI2Cards->Width) / 2, 0);

	
	AI3Cards->Height = maxWidth / 2 + CARD_WIDTH;
	AI3Cards->Width = maxHeight * 2;
	AI3Cards->Location = Point(this->Width - AI3Cards->Width, (this->Height - AI3Cards->Height) / 2);

	srand(time(nullptr));
	president = new PresidentI;

	List<FlowLayoutPanel^>^ cardsContainers = gcnew List<FlowLayoutPanel^>;

	cardsContainers->Add(humanCards);
	cardsContainers->Add(AI1Cards);
	cardsContainers->Add(AI2Cards);
	cardsContainers->Add(AI3Cards);

	president->displayAllCards(cardsContainers);
}

PresidentForm::~PresidentForm() {
	if (components)
		delete components;
	
	delete president;
}