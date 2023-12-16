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
		cardInfo^ info = gcnew cardInfo;
		info->name = card->getName();
		info->suit = card->getSuit();
		picture->Tag = info;
		cardsContainer->Controls->Add(picture);
		Application::DoEvents();
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
	while (cardsContainer->Controls->Count > 0)
		cardsContainer->Controls->Remove(cardsContainer->Controls[0]);
}

Card* PresidentI::getHumanCardFromCardInfo(Object^ info) {
	cardInfo^ clickedCardInfo = dynamic_cast<cardInfo^>(info);
	for (auto card : humanPlayer->getCards()) {
		if (card->getName() == clickedCardInfo->name && card->getSuit() == clickedCardInfo->suit)
			return card;
	}
	return nullptr;
}

void PresidentI::setCardsOnDesk(vector<Card*> cards) {
	cardsOnDesk.clear();
	copy(cards.begin(), cards.end(), back_inserter(cardsOnDesk));
	displayCards(cardsContainers::containers[CARDS_ON_DESK_CONTAINER], cardsOnDesk, RotateFlipType::RotateNoneFlipNone);
}

void PresidentI::makeHumanMove(Object^ info) {
	cardsOnDesk.clear();
	Card* selectedCard = getHumanCardFromCardInfo(info);
	humanPlayer->selectCardsForTurn(selectedCard);
	vector<Card*> playedCards(humanPlayer->makeTurn());
	setCardsOnDesk(playedCards);
	removeCards(cardsContainers::containers[HUMAN_CONTAINER], playedCards);

	Sleep(2000);

	makeAIPlayersMoves();
}

void PresidentI::makeAIPlayersMoves() {
	for (int i = 0; i < AIPlayers.size(); ++i) {
		AIPlayers.at(i)->setCardsToBeat(cardsOnDesk);
		AIPlayers.at(i)->selectCardsForTurn();
		vector<Card*> playedCards(AIPlayers.at(i)->makeTurn());

		if (!playedCards.empty()) {
			setCardsOnDesk(playedCards);
			label::resultLabel->Text = "AI player " + (i + 1) + " made turn";
		} else {
			label::resultLabel->Text = "AI player " + (i + 1) + " can't make turn";
		}

		Application::DoEvents();

		removeCards(cardsContainers::containers[i+1], playedCards);
		Sleep(2000);
	}

	label::resultLabel->Text = "Your turn";
}

void PresidentI::removeCards(FlowLayoutPanel^ cardsContainer, vector<Card*> cards) {
	int i = 0;
	while (i < cardsContainer->Controls->Count) {
		PictureBox^ pictureBoxCard = dynamic_cast<PictureBox^>(cardsContainer->Controls[i]);
		cardInfo^ info = dynamic_cast<cardInfo^>(pictureBoxCard->Tag);

		for (auto card : cards) {
			if (card->getName() == info->name && card->getSuit() == info->suit) {
				Control^ element = cardsContainer->Controls[i];
				cardsContainer->Controls->Remove(element);
				--i;
			}
		}
		++i;
	}
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
