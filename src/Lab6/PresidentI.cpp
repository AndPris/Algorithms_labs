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
			displayCards(cardsContainers::containers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::RotateNoneFlipNone, true);
		else
			displayCards(cardsContainers::containers[i + 1], AIPlayers.at(i)->getCards(), RotateFlipType::Rotate90FlipNone, true);
	}

	displayCards(cardsContainers::containers[CARDS_ON_DESK_CONTAINER], cardsOnDesk, RotateFlipType::RotateNoneFlipNone);
}

void PresidentI::displayCards(FlowLayoutPanel^ cardsContainer, vector<Card*> cards, RotateFlipType rotationDegree, bool hide) {
	clearCardsContainer(cardsContainer);

	for (auto card : cards) {
		String^ cardPath;
		if (hide)
			cardPath = "cards\\back_side.png";
		else
			cardPath = gcnew String(getCardPath(card).c_str());
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
	vector<Card*> cards = humanPlayer->getCards();
	for (auto card : cards) {
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

WinResults PresidentI::makeHumanMove(Object^ info) {
	Card* selectedCard = getHumanCardFromCardInfo(info);
	if (!humanPlayer->selectCardsForTurn(selectedCard)) {
		changeResultLabelText("You can't make turn using these cards");
		return NO_WIN;
	}
	disableHumanPlayerCards();
	vector<Card*> playedCards(humanPlayer->makeTurn());
	setCardsOnDesk(playedCards);
	removeCards(cardsContainers::containers[HUMAN_CONTAINER], playedCards);
	lastActingPlayer = humanPlayer;

	if (checkWinCondition() == HUMAN_WIN) {
		changeResultLabelText("You won!");
		return HUMAN_WIN;
	}

	Sleep(PAUSE);
	if (makeAIPlayersMoves() == AI_WIN)
		return AI_WIN;
}

WinResults PresidentI::makeAIPlayersMoves() {
	for (int i = 0; i < AIPlayers.size(); ++i) {
		if (lastActingPlayer == AIPlayers.at(i)) {
			changeResultLabelText("No one could beat " + (i+1) + " AI player's cards!");
			setCardsOnDesk(vector<Card*>{});
			Sleep(PAUSE / 2);
		}

		AIPlayers.at(i)->setCardsToBeat(cardsOnDesk);
		AIPlayers.at(i)->selectCardsForTurn();
		vector<Card*> playedCards(AIPlayers.at(i)->makeTurn());

		if (!playedCards.empty()) {
			setCardsOnDesk(playedCards);
			changeResultLabelText("AI player " + (i + 1) + " made turn");
			lastActingPlayer = AIPlayers.at(i);
		} else {
			changeResultLabelText("AI player " + (i + 1) + " can't make turn");
		}

		removeCards(cardsContainers::containers[i+1], playedCards);

		if (checkWinCondition() == AI_WIN) {
			changeResultLabelText("AI player " + (i + 1) + " won!");
			return AI_WIN;
		}
		Sleep(PAUSE);
	}

	if (lastActingPlayer == humanPlayer) {
		changeResultLabelText("No one could beat your cards!");
		setCardsOnDesk(vector<Card*>{});
		Sleep(PAUSE / 2);
	}
	humanPlayer->setCardsToBeat(cardsOnDesk);
	if (!humanPlayer->canFightBack()) {
		changeResultLabelText("You can't beat these cards");
		Sleep(PAUSE);
		if (makeAIPlayersMoves() == AI_WIN)
			return AI_WIN;
	} else {
		changeResultLabelText("Your turn");
	}
	enableHumanPlayerCards();
}

void PresidentI::changeResultLabelText(String^ newText) {
	label::resultLabel->Text = newText;
	Application::DoEvents();
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

void PresidentI::disableHumanPlayerCards() {
	cardsContainers::containers[HUMAN_CONTAINER]->Enabled = false;

	for each (Control ^ control in cardsContainers::containers[HUMAN_CONTAINER]->Controls)
		control->Enabled = false;

	Application::DoEvents();
}

void PresidentI::enableHumanPlayerCards() {
	cardsContainers::containers[HUMAN_CONTAINER]->Enabled = true;

	for each (Control ^ control in cardsContainers::containers[HUMAN_CONTAINER]->Controls)
		control->Enabled = true;

	Application::DoEvents();
}


void PresidentI::restart() {
	deck->fill();
	deck->shuffle();

	humanPlayer->clearAllCards();
	for (auto player : AIPlayers)
		player->clearAllCards();

	cardsOnDesk.clear();
	distributeCards();
	displayAllCards();
	changeResultLabelText("Your turn");
	enableHumanPlayerCards();
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
