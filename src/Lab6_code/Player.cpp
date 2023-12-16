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

		for (int j = 0; j < cardsToBeat.size(); ++j) {
			if (i + j >= cards.size()) {
				i = cards.size();
				selectedCards.clear();
				break;
			}

			selectedCards.push_back(cards.at(i + j));

			if (!(*selectedCards.at(j) == *selectedCards.at(0))) {
				selectedCards.clear();
				i += j;
				break;
			}
		}

		if (!selectedCards.empty())
			break;
	}
}

void HumanPlayer::selectCardsForTurn(Card* selectedCard) {
	for (auto card : cards) {
		if (*card == *selectedCard)
			selectedCards.push_back(card);
	}
}
