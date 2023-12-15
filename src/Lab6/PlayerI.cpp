#include "PlayerI.h"

string PlayerI::getCardPath(Card* card) {
	string path = "";

	switch (card->getName()) {
	case TWO:
		path += "2";
		break;
	case THREE:
		path += "3";
		break;
	case FOUR:
		path += "4";
		break;
	case FIVE:
		path += "5";
		break;
	case SIX:
		path += "6";
		break;
	case SEVEN:
		path += "7";
		break;
	case EIGHT:
		path += "8";
		break;
	case NINE:
		path += "9";
		break;
	case TEN:
		path += "10";
		break;
	case JACK:
		path += "jack";
		break;
	case QUEEN:
		path += "queen";
		break;
	case KING:
		path += "king";
		break;
	case ACE:
		path += "ace";
		break;
	}

	path += "_of_";

	switch (card->getSuit()) {
	case CLUBS:
		path += "clubs";
		break;
	case DIAMONDS:
		path += "diamonds";
		break;
	case HEARTS:
		path += "hearts";
		break;
	case SPADES:
		path += "spades";
		break;
	}

	path += ".png";
	return path;
}

void PlayerI::clearCardsContainer(FlowLayoutPanel^ cardsContainer) {
	for each (Control ^ control in cardsContainer->Controls)
		cardsContainer->Controls->Remove(control);
}

PlayerI::PlayerI(Player* player) {
	this->player = player;
}

void PlayerI::display(FlowLayoutPanel^ cardsContainer) {
	clearCardsContainer(cardsContainer);

	const int cardWidth = 100;
	const int cardHeight = 150;
	const int spacing = 10;

	int x = 0;
	int y = 0;

	for (auto card : player->getCards()) {
		string cardPath = getCardPath(card);

		PictureBox^ pictureBoxCard = gcnew PictureBox();
		pictureBoxCard->Image = Image::FromFile(gcnew String(cardPath.c_str()));
		pictureBoxCard->SizeMode = PictureBoxSizeMode::Zoom;
		pictureBoxCard->Size = Size(cardWidth, cardHeight);
		pictureBoxCard->Location = Point(x, y);

		cardsContainer->Controls->Add(pictureBoxCard);

		x += cardWidth + spacing;
	}
}

void PlayerI::addCard(Card* card) {
	player->addCard(card);
}

PlayerI::~PlayerI() {
	delete player;
}

