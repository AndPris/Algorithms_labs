#pragma once

enum Suits {
	CLUBS,		//хреста
	DIAMONDS,	//бубна
	HEARTS,		//черва
	SPADES,		//піка
};

enum CardNames {
	TREE = 1,
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