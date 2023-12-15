#pragma once

#include "Cards.h"
#include <iterator>

class Player {
protected:
	vector<Card*> cards;
	vector<Card*> selectedCards;
	vector<Card*> cardsToBeat;

	int findPositionForCard(Card* card);

	virtual void selectCardsForTurn() = 0;

public:
	void addCard(Card* card);
	vector<Card*> getCards();
	void setCardsToBeat(vector<Card*> cards);
	vector<Card*> makeTurn();
	bool hasWon() const;
};


class AIPlayer : public Player {
	void selectCardsForTurn() override;
	void selectCardsForFirstTurn();
	void selectCardsForBeatTurn();
public:

};


class HumanPlayer : public Player {
	void selectCardsForTurn() override;
};