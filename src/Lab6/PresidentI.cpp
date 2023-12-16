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

void PresidentI::displayAllCards() {
	displayCards(cardsContainers::containers[0], humanPlayer->getCards(), RotateFlipType::RotateNoneFlipNone);
	setHumanCardsInfo(cardsContainers::containers[0], humanPlayer->getCards());

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i) {
		if(i%2 == 1)
			displayCards(cardsContainers::containers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::RotateNoneFlipNone);
		else
			displayCards(cardsContainers::containers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::Rotate90FlipNone);
	}

	displayCards(cardsContainers::containers[AMOUNT_OF_AI_PLAYERS + 1], cardsOnDesk, RotateFlipType::RotateNoneFlipNone);
}

void PresidentI::displayCards(FlowLayoutPanel^ cardsContainer, vector<Card*> cards, RotateFlipType rotationDegree) {
	clearCardsContainer(cardsContainer);

	for (auto card : cards) {
		String^ cardPath = gcnew String(getCardPath(card).c_str());
		PictureBox^ picture = getPicture(cardPath, rotationDegree);
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

	pictureBoxCard->Margin = Padding(0, 0, PADDING, 0);

	return pictureBoxCard;
}

void PresidentI::clearCardsContainer(FlowLayoutPanel^ cardsContainer) {
	for each (Control ^ control in cardsContainer->Controls)
		cardsContainer->Controls->Remove(control);
}

void PresidentI::setHumanCardsInfo(FlowLayoutPanel^ cardsContainer, vector<Card*> cards) {
	for (int i = 0; i < cards.size(); ++i) {
		cardInfo^ info = gcnew cardInfo;
		info->name = cards.at(i)->getName();
		info->suit = cards.at(i)->getSuit();

		PictureBox^ pictureBoxCard = dynamic_cast<PictureBox^>(cardsContainer->Controls[i]);

		pictureBoxCard->Tag = info;
	}
}

Card* PresidentI::getHumanCardFromCardInfo(Object^ info) {
	cardInfo^ clickedCardInfo = dynamic_cast<cardInfo^>(info);
	for (auto card : humanPlayer->getCards()) {
		if (card->getName() == clickedCardInfo->name && card->getSuit() == clickedCardInfo->suit)
			return card;
	}
	return nullptr;
}

void PresidentI::setCardsOnDesc(vector<Card*> cards) {
	copy(cards.begin(), cards.end(), back_inserter(cardsOnDesk));
	displayCards(cardsContainers::containers[CARDS_ON_DESK_CONTAINER], cardsOnDesk, RotateFlipType::RotateNoneFlipNone);
}

void PresidentI::makeHumanMove(Object^ info) {
	cardsOnDesk.clear();
	Card* selectedCard = getHumanCardFromCardInfo(info);
	humanPlayer->selectCardsForTurn(selectedCard);
	vector<Card*> playedCards = humanPlayer->makeTurn();
	setCardsOnDesc(playedCards);
	removeHumanCards(playedCards);
}

void PresidentI::removeHumanCards(vector<Card*> cards) {
	for each (Control ^ control in cardsContainers::containers[HUMAN_CONTAINER]->Controls) {
		PictureBox^ pictureBoxCard = dynamic_cast<PictureBox^>(control);
		cardInfo^ info = dynamic_cast<cardInfo^>(pictureBoxCard->Tag);

		for (auto card : cards) {
			if (card->getName() == info->name && card->getSuit() == info->suit)
				cardsContainers::containers[HUMAN_CONTAINER]->Controls->Remove(control);
		}
	}
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
