#include "PresidentForm.h"
#include <stdlib.h>
#include <ctime>

using namespace Lab6;


PresidentForm::PresidentForm(void) {
	InitializeComponent();

	const int maxAmountOfCards = 13;
	int maxWidth = (CARD_WIDTH + PADDING) * maxAmountOfCards;
	int maxHeight = CARD_HEIGHT;

	humanCards->Height = maxHeight+60;
	humanCards->Width = maxWidth;
	humanCards->Location = Point((this->Width - humanCards->Width) / 2, this->Height - humanCards->Height);

	AI1Cards->Height = maxWidth/2 + CARD_WIDTH - 6*PADDING;
	AI1Cards->Width = maxHeight*2;
	AI1Cards->Location = Point(0, (this->Height - AI1Cards->Height)/2);

	AI2Cards->Height = maxHeight;
	AI2Cards->Width = maxWidth;
	AI2Cards->Location = Point((this->Width - AI2Cards->Width) / 2, 0);

	
	AI3Cards->Height = maxWidth / 2 + CARD_WIDTH;
	AI3Cards->Width = maxHeight * 2;
	AI3Cards->Location = Point(this->Width - AI3Cards->Width + CARD_WIDTH, (this->Height - AI3Cards->Height) / 2);

	cardsOnDesk->Height = maxHeight;
	cardsOnDesk->Width = (CARD_WIDTH + PADDING) * 4;
	cardsOnDesk->Location = Point((this->Width - cardsOnDesk->Width) / 2, (this->Height - cardsOnDesk->Height) / 2);

	srand(time(nullptr));
	president = new PresidentI;

	cardsContainers::containers->Add(humanCards);
	cardsContainers::containers->Add(AI1Cards);
	cardsContainers::containers->Add(AI2Cards);
	cardsContainers::containers->Add(AI3Cards);
	cardsContainers::containers->Add(cardsOnDesk);

	president->displayAllCards();
	setCardsClickHandlers();
}

void PresidentForm::setCardsClickHandlers() {
	for each (Control ^ control in humanCards->Controls) {
		PictureBox^ pictureBoxCard = dynamic_cast<PictureBox^>(control);
		pictureBoxCard->Click += gcnew System::EventHandler(this, &PresidentForm::Card_Click);
	}
}

Void PresidentForm::Card_Click(Object^ sender, EventArgs^ e) {
	PictureBox^ clickedPictureBox = dynamic_cast<PictureBox^>(sender);
	president->makeHumanMove(clickedPictureBox->Tag);
}

PresidentForm::~PresidentForm() {
	if (components)
		delete components;
	
	delete president;
}