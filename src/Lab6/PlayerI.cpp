#include "PlayerI.h"

string PlayerI::getCardPath(Card* card) {
	string path = "cards\\";

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

PlayerI::PlayerI(Player* player, RotateFlipType rotationDegree) {
	this->player = player;
	this->rotationDegree = rotationDegree;
}

PictureBox^ PlayerI::getPicture(String^ cardPath) {
	PictureBox^ pictureBoxCard = gcnew PictureBox();
	pictureBoxCard->Image = Image::FromFile(cardPath);
	pictureBoxCard->Image->RotateFlip(rotationDegree);
	pictureBoxCard->SizeMode = PictureBoxSizeMode::Zoom;

	if (rotationDegree == RotateFlipType::Rotate90FlipNone || rotationDegree == RotateFlipType::Rotate270FlipNone)
		pictureBoxCard->Size = Size(CARD_HEIGHT, CARD_WIDTH);
	else
		pictureBoxCard->Size = Size(CARD_WIDTH, CARD_HEIGHT);

	pictureBoxCard->Margin = Padding(0, 0, 5, 0);

	return pictureBoxCard;
}

void PlayerI::addCard(Card* card) {
	player->addCard(card);
}

bool PlayerI::hasWon() const {
	return player->hasWon();
}

PlayerI::~PlayerI() {
	delete player;
}



void AIPlayerI::display(FlowLayoutPanel^ cardsContainer) {
	clearCardsContainer(cardsContainer);

	for (auto card : player->getCards()) {
		String^ cardPath = gcnew String(getCardPath(card).c_str());
		cardsContainer->Controls->Add(getPicture(cardPath));
	}
}


void HumanPlayerI::display(FlowLayoutPanel^ cardsContainer) {
	clearCardsContainer(cardsContainer);

	for (auto card : player->getCards()) {
		String^ cardPath = gcnew String(getCardPath(card).c_str());
		PictureBox^ picture = getPicture(cardPath);

		cardInfo^ info = gcnew cardInfo;
		info->name = card->getName();
		info->suit = card->getSuit();

		picture->Tag = info;

		cardsContainer->Controls->Add(picture);
	}
}