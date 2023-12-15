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