#include "PresidentI.h"


PresidentI::PresidentI() {
	deck = new Deck();
	humanPlayer = new PlayerI(new HumanPlayer, RotateFlipType::RotateNoneFlipNone);

	List<RotateFlipType> rotationDegrees;
	rotationDegrees.Add(RotateFlipType::Rotate90FlipNone);
	rotationDegrees.Add(RotateFlipType::Rotate180FlipNone);
	rotationDegrees.Add(RotateFlipType::Rotate270FlipNone);

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i) {
		PlayerI* AIPlayerI = new PlayerI(new AIPlayer, rotationDegrees[i]);
		AIPlayers.push_back(AIPlayerI);
	}

	distributeCards();

	president = nullptr;
	poorMan = nullptr;
}

void PresidentI::distributeCards() {
	const int deckSize = 52;

	for (int i = 0; i < deckSize / (AMOUNT_OF_AI_PLAYERS + 1); ++i) {
		humanPlayer->addCard(deck->getCard());
		for (int j = 0; j < AMOUNT_OF_AI_PLAYERS; ++j)
			AIPlayers.at(j)->addCard(deck->getCard());
	}
}

void PresidentI::displayAllCards(List<FlowLayoutPanel^>^ cardsContainers) {
	humanPlayer->display(cardsContainers[0]);

	for (int i = 0; i < AMOUNT_OF_AI_PLAYERS; ++i)
		AIPlayers.at(i)->display(cardsContainers[i+1]);
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
