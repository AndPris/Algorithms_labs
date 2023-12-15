#pragma once

#include "PlayerI.h"
using namespace System::Collections::Generic;
#define AMOUNT_OF_AI_PLAYERS 3

class PresidentI {
	Deck* deck;
	//vector<Card*> discard;
	vector<Card*> cardsOnDesk;

	vector<PlayerI*> AIPlayers;
	PlayerI* humanPlayer;

	//Player* current
	Player* president;
	Player* poorMan;

	void distributeCards();
public:
	PresidentI();

	void displayAllCards(List<FlowLayoutPanel^>^ cardsContainers);

	~PresidentI();
};

