#include "Player.h"

int Player::findPositionForCard(Card* card) {
	int index = 0;

	while (index < cards.size() && *card > *cards.at(index))
		++index;

	return index;
}

void Player::removeSelectedCardsFromAllCards() {
	if (selectedCards.empty())
		return;

	for (auto card : cards) {
		if (card == selectedCards.at(0))
			cards.erase(find(cards.begin(), cards.end(), card));
	}
}

void Player::selectCardsToFightBack(Card* anchorCard) {
	for (auto card : cards) {
		if (*card == *anchorCard && selectedCards.size() < cardsToBeat.size())
			selectedCards.push_back(card);
	}

	if (selectedCards.size() != cardsToBeat.size())
		selectedCards.clear();
}

void Player::addCard(Card* card) {
	int index = findPositionForCard(card);
	cards.insert(cards.begin() + index, card);
}

vector<Card*> Player::getCards() {
	return cards;
}

vector<Card*> Player::getSelectedCards() {
	return selectedCards;
}

void Player::setCardsToBeat(vector<Card*> cards) {
	copy(cards.begin(), cards.end(), back_inserter(cardsToBeat));
}

vector<Card*> Player::makeTurn() {
	removeSelectedCardsFromAllCards();

	vector<Card*> cardsToReturn;
	copy(selectedCards.begin(), selectedCards.end(), back_inserter(cardsToReturn));
	
	selectedCards.clear();
	cardsToBeat.clear();

	return cardsToReturn;
}

bool Player::hasWon() const {
	return cards.empty();
}



void AIPlayer::selectCardsForTurn() {
	if (cardsToBeat.empty())
		selectCardsForFirstTurn();
	else
		selectCardsForBeatTurn();
}

void AIPlayer::selectCardsForFirstTurn() {
	int i = 0;

	while (i < cards.size() && *cards.at(0) == *cards.at(i)) {
		selectedCards.push_back(cards.at(i));
		++i;
	}
}

void AIPlayer::selectCardsForBeatTurn() {
	int i = 0;
	while(i < cards.size()) {
		if (*cardsToBeat.at(0) > *cards.at(i) || *cardsToBeat.at(0) == *cards.at(i)) {
			++i;
			continue;
		}
		selectCardsToFightBack(cards.at(i));
		if (!selectedCards.empty())
			break;

		++i; 
	}
}

bool HumanPlayer::selectCardsForTurn(Card* selectedCard) {
	if (cardsToBeat.empty()) {
		for (auto card : cards) {
			if (*card == *selectedCard)
				selectedCards.push_back(card);
		}

		return true;
	}

	if (!(*selectedCard > *cardsToBeat.at(0)))
		return false;

	selectCardsToFightBack(selectedCard);

	return selectedCards.size() > 0;
}

bool HumanPlayer::canFightBack() {
	if (cardsToBeat.empty())
		return true;

	for (auto card : cards) {
		if (!(*card > *cardsToBeat.front()))
			continue;

		selectCardsToFightBack(card);

		if (!selectedCards.empty()) {
			selectedCards.clear();
			return true;
		}
	}

	return false;
}
