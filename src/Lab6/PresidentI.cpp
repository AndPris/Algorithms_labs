#include "PresidentI.h"


PresidentI::PresidentI() {
	deck = new Deck();
	humanPlayer = new PlayerI(new HumanPlayer);

	distributeCards();

	president = nullptr;
	poorMan = nullptr;
}

void PresidentI::distributeCards() {
	const int deckSize = 52;

	for (int i = 0; i < 14; ++i)
		humanPlayer->addCard(deck->getCard());
}

void PresidentI::displayAllCards(FlowLayoutPanel^ cardsContainer) {
	humanPlayer->display(cardsContainer);
}

PresidentI::~PresidentI() {
	delete deck;
	delete humanPlayer;
}
