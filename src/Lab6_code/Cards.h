#pragma once

#include <vector>
#include <algorithm>

using namespace std;


enum Suits {
	CLUBS,		//хреста
	DIAMONDS,	//бубна
	HEARTS,		//черва
	SPADES,		//піка
};

enum CardNames {
	THREE = 1,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	TWO,
};

class Card {
	Suits suit;
	CardNames name;

public:
	Card(Suits suit, CardNames name);

	Suits getSuit() const;
	CardNames getName() const;

	bool operator==(const Card& obj) const;
	bool operator>(const Card& obj) const;
};


class Deck {
	vector<Card*> cards;

public:
	Deck();

	void shuffle();
	Card* getCard();

	bool isEmpty() const;

	~Deck();
};