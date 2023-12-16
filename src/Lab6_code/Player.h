#pragma once

#include "Cards.h"
#include <iterator>

class Player {
protected:
	vector<Card*> cards;
	vector<Card*> selectedCards;
	vector<Card*> cardsToBeat;

	int findPositionForCard(Card* card);

	void removeSelectedCardsFromAllCards();
	void selectCardsToFightBack(Card* anchorCard);
public:
	void addCard(Card* card);
	vector<Card*> getCards();
	vector<Card*> getSelectedCards();
	void setCardsToBeat(vector<Card*> cards);
	vector<Card*> makeTurn();
	bool hasWon() const;
};


class AIPlayer : public Player {
	void selectCardsForFirstTurn();
	void selectCardsForBeatTurn();
public:
	void selectCardsForTurn();
};


class HumanPlayer : public Player {
public:
	bool selectCardsForTurn(Card* selectedCard);
	bool canFightBack();
};