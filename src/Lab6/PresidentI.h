#pragma once

#include "PlayerI.h"

class PresidentI {
	Deck* deck;
	vector<Card*> discard;
	vector<Card*> cardsOnDesk;

	//vector<AIPlayer*> AIPlayers;
	PlayerI* humanPlayer;

	//Player* current
	Player* president;
	Player* poorMan;

	void distributeCards();
public:
	PresidentI();

	void displayAllCards(FlowLayoutPanel^ cardsContainer);

	~PresidentI();
};

