#include "Cards.h"

Card::Card(Suits suit, CardNames name) {
	this->suit = suit;
	this->name = name;
}

Suits Card::getSuit() const {
	return suit;
}

CardNames Card::getName() const {
	return name;
}

bool Card::operator==(const Card& obj) const {
	return this->name == obj.name;
}

bool Card::operator>(const Card& obj) const {
	return this->name > obj.name;
}



Deck::Deck() {
	vector<Suits> suits = { CLUBS, DIAMONDS, HEARTS, SPADES };
	vector<CardNames> cardNames = { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

	for (auto suit : suits) {
		for (auto cardName : cardNames) {
			Card *card = new Card(suit, cardName);
			cards.push_back(card);
		}
	}

	shuffle();
}

void Deck::shuffle() {
	random_shuffle(cards.begin(), cards.end());
}

Card* Deck::getCard() {
	if (cards.empty())
		return nullptr;

	Card* card = cards.back();
	cards.pop_back();
	return card;
}

bool Deck::isEmpty() const {
	return cards.empty();
}

Deck::~Deck() {
	for (auto card : cards)
		delete card;
}