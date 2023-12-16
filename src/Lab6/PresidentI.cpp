#include "PresidentI.h"


PresidentI::PresidentI() {
	deck = new Deck();
	humanPlayer = new HumanPlayer;

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i) {
		AIPlayer* bot = new AIPlayer;
		AIPlayers.push_back(bot);
	}

	distributeCards();
}

void PresidentI::distributeCards() {
	const int deckSize = 52;

	for (int i = 0; i < deckSize / (AMOUNT_OF_AI_PLAYERS + 1); ++i) {
		humanPlayer->addCard(deck->getCard());
		for (int j = 0; j < AMOUNT_OF_AI_PLAYERS; ++j)
			AIPlayers.at(j)->addCard(deck->getCard());
	}
}

WinResults PresidentI::checkWinCondition() const {
	if (humanPlayer->hasWon())
		return HUMAN_WIN;

	for (auto AIPlayer : AIPlayers) {
		if (AIPlayer->hasWon())
			return AI_WIN;
	}

	return NO_WIN;
}

void PresidentI::displayAllCards(List<FlowLayoutPanel^>^ cardsContainers) {
	displayCards(cardsContainers[0], humanPlayer->getCards(), RotateFlipType::RotateNoneFlipNone);

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i) {
		if(i%2 == 1)
			displayCards(cardsContainers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::RotateNoneFlipNone);
		else
			displayCards(cardsContainers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::Rotate90FlipNone);
	}
}

void PresidentI::displayCards(FlowLayoutPanel^ cardsContainer, vector<Card*> cards, RotateFlipType rotationDegree) {
	clearCardsContainer(cardsContainer);

	for (auto card : cards) {
		String^ cardPath = gcnew String(getCardPath(card).c_str());
		PictureBox^ picture = getPicture(cardPath, rotationDegree);

		cardInfo^ info = gcnew cardInfo;
		info->name = card->getName();
		info->suit = card->getSuit();

		picture->Tag = info;

		cardsContainer->Controls->Add(picture);
	}
}

string PresidentI::getCardPath(Card* card) {
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

PictureBox^ PresidentI::getPicture(String^ cardPath, RotateFlipType rotationDegree) {
	PictureBox^ pictureBoxCard = gcnew PictureBox();
	pictureBoxCard->Image = Image::FromFile(cardPath);
	pictureBoxCard->Image->RotateFlip(rotationDegree);
	pictureBoxCard->SizeMode = PictureBoxSizeMode::Zoom;

	if (rotationDegree == RotateFlipType::Rotate90FlipNone)
		pictureBoxCard->Size = Size(CARD_HEIGHT, CARD_WIDTH);
	else
		pictureBoxCard->Size = Size(CARD_WIDTH, CARD_HEIGHT);

	pictureBoxCard->Margin = Padding(0, 0, 5, 0);

	return pictureBoxCard;
}

void PresidentI::clearCardsContainer(FlowLayoutPanel^ cardsContainer) {
	for each (Control ^ control in cardsContainer->Controls)
		cardsContainer->Controls->Remove(control);
}


void PresidentI::game(List<FlowLayoutPanel^>^ cardsContainers) {
	do {
		displayAllCards(cardsContainers);

	} while (checkWinCondition() == NO_WIN);
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
