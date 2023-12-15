#pragma once

#include "PlayerI.h"
using namespace System::Collections::Generic;
#define AMOUNT_OF_AI_PLAYERS 3

enum WinResults {
	NO_WIN,
	HUMAN_WIN,
	AI_WIN
};

class PresidentI {
	Deck* deck;
	vector<Card*> cardsOnDesk;

	vector<AIPlayerI*> AIPlayers;
	HumanPlayerI* humanPlayer;

	void distributeCards();
	WinResults checkWinCondition() const;
public:
	PresidentI();

	void displayAllCards(List<FlowLayoutPanel^>^ cardsContainers);
	void game(List<FlowLayoutPanel^>^ cardsContainers);

	~PresidentI();
};

