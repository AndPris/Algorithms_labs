#include "Player.h"

int Player::findPositionForCard(Card* card) {
	int index = 0;

	while (index < cards.size() && *card > *cards.at(index))
		++index;

	return index;
}

void Player::addCard(Card* card) {
	int index = findPositionForCard(card);
	cards.insert(cards.begin() + index, card);
}

void Player::setCardsToBeat(vector<Card*> cards) {
	copy(cards.begin(), cards.end(), back_inserter(cardsToBeat));
}

vector<Card*> Player::makeTurn() {
	selectCardsForTurn();

	if(!selectedCards.empty())
		cards.erase(cards.begin(), cards.begin() + selectedCards.size());

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

	while (i < cards.size() && cards.at(0) == cards.at(i)) {
		selectedCards.push_back(cards.at(i));
		++i;
	}
}

void AIPlayer::selectCardsForBeatTurn() {
	int i = 0;
	while(i < cards.size()) {
		if (cardsToBeat.at(0) > cards.at(i)) {
			++i;
			continue;
		}

		for (int j = 0; j < cardsToBeat.size(); ++j) {
			selectedCards.push_back(cards.at(i + j));

			if (!(selectedCards.at(j) == selectedCards.at(0))) {
				selectedCards.clear();
				i += j;
				break;
			}
		}

		if (!selectedCards.empty())
			break;
	}
}
