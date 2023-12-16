#pragma once

#include "../Lab6_code/Player.h"
#include <string>
#include <Windows.h>

using namespace System;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Reflection;
using namespace std;

#define AMOUNT_OF_AI_PLAYERS 3
#define CARD_WIDTH 72
#define CARD_HEIGHT 130


enum WinResults {
	NO_WIN,
	HUMAN_WIN,
	AI_WIN
};

ref class cardInfo {
public:
	Suits suit;
	CardNames name;
};

class PresidentI {
	Deck* deck;
	vector<Card*> cardsOnDesk;

	vector<AIPlayer*> AIPlayers;
	HumanPlayer* humanPlayer;

	void distributeCards();
	WinResults checkWinCondition() const;
	void displayCards(FlowLayoutPanel^ cardContainer, vector<Card*> cards, RotateFlipType rotationDegree);
	void clearCardsContainer(FlowLayoutPanel^ cardsContainer);
	string getCardPath(Card* card);
	PictureBox^ getPicture(String^ cardPath, RotateFlipType rotationDegree);
public:
	PresidentI();

	void displayAllCards(List<FlowLayoutPanel^>^ cardsContainers);
	void game(List<FlowLayoutPanel^>^ cardsContainers);

	~PresidentI();
};

