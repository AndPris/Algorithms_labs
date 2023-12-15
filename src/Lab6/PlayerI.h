#pragma once

#include "../Lab6_code/Player.h"
#include <string>
#include <Windows.h>

#define CARD_WIDTH 72
#define CARD_HEIGHT 130

using namespace System;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Reflection;
using namespace std;


ref class cardInfo {
public:
	Suits suit;
	CardNames name;
};


class PlayerI {
protected:
	Player* player;

	RotateFlipType rotationDegree;

	string getCardPath(Card* card);
	void clearCardsContainer(FlowLayoutPanel^ cardsContainer);
	PictureBox^ getPicture(String^ cardPath);
public:
	PlayerI(Player* player, RotateFlipType rotationDegree);

	virtual void display(FlowLayoutPanel^ cardsContainer) = 0;

	void addCard(Card* card);
	bool hasWon() const;

	~PlayerI();
};



class AIPlayerI : public PlayerI {
public:
	void display(FlowLayoutPanel^ cardsContainer) override;

};



class HumanPlayerI : public PlayerI {
public:
	HumanPlayerI(Player* player, RotateFlipType rotationDegree) : PlayerI(player, rotationDegree) {};

	void display(FlowLayoutPanel^ cardsContainer) override;
};