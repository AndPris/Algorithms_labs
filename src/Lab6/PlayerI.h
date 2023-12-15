#pragma once

#include "../Lab6_code/Player.h"
#include <string>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
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

