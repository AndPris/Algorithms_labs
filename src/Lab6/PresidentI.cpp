#include "PresidentI.h"


PresidentI::PresidentI() {
	deck = new Deck();
	humanPlayer = new HumanPlayerI(new HumanPlayer, RotateFlipType::RotateNoneFlipNone);

	List<RotateFlipType> rotationDegrees;
	rotationDegrees.Add(RotateFlipType::Rotate90FlipNone);
	rotationDegrees.Add(RotateFlipType::Rotate180FlipNone);
	rotationDegrees.Add(RotateFlipType::Rotate270FlipNone);

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i) {
		AIPlayerI* bot = new AIPlayerI(new AIPlayer, rotationDegrees[i]);
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
	humanPlayer->display(cardsContainers[0]);

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i)
		AIPlayers.at(i)->display(cardsContainers[i+1]);
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
