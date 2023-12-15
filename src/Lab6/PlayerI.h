#pragma once

#include "../Lab6_code/Player.h"
#include <string>
#include <Windows.h>

#define CARD_WIDTH 90
#define CARD_HEIGHT 140
#define SPACING 5

using namespace System;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Reflection;
using namespace std;


class PlayerI {
	Player* player;

	string getCardPath(Card* card);
	void clearCardsContainer(FlowLayoutPanel^ cardsContainer);
public:
	PlayerI(Player* player);

	void display(FlowLayoutPanel^ cardsContainer);

	void addCard(Card* card);

	~PlayerI();
};

