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
#define PADDING 5

ref class cardsContainers {
public:
	static List<FlowLayoutPanel^>^ containers = gcnew List<FlowLayoutPanel^>;
};

enum containersNumbers{
	HUMAN_CONTAINER,
	AI1_CONTAINER,
	AI2_CONTAINER,
	AI3_CONTAINER,
	CARDS_ON_DESK_CONTAINER,
};

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
	void setHumanCardsInfo(FlowLayoutPanel^ cardsContainer, vector<Card*> cards);
	Card* getHumanCardFromCardInfo(Object^ info);
public:
	PresidentI();

	void displayAllCards();

	void setCardsOnDesc(vector<Card*> cards);
	void removeHumanCards(vector<Card*> cards);

	void makeHumanMove(Object^ info);

	~PresidentI();
};