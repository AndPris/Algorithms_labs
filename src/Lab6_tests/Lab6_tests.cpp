#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab6_code/Cards.h"
#include "../Lab6_code/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab6tests
{
	bool areEqual(Card* card1, Card* card2) {
		return card1->getName() == card2->getName() && card1->getSuit() == card2->getSuit();
	}

	bool contains(vector<Card*> cards, Card* card) {
		for (auto availableCard : cards) {
			if (areEqual(card, availableCard))
				return true;
		}
		return false;
	}

	bool areEqual(vector<Card*> cards1, vector<Card*> cards2) {
		if (cards1.size() != cards2.size())
			return false;

		for (auto card1 : cards1) {
			if (!contains(cards2, card1))
				return false;
		}
		return true;
	}

	TEST_CLASS(CardTests)
	{
	private:
		Suits suit;
		CardNames name;
		Card* card;
	public:
		CardTests() {
			suit = HEARTS;
			name = TEN;
			card = new Card(suit, name);
		}

		TEST_METHOD(getSuitTest)
		{
			Assert::IsTrue(suit == card->getSuit());
		}

		TEST_METHOD(getNameTest)
		{
			Assert::IsTrue(name == card->getName());
		}
		
		TEST_METHOD(equalOperatorTest1)
		{
			Card testCard(suit, name);
			Assert::IsTrue(testCard == *card);
		}

		TEST_METHOD(equalOperatorTest2)
		{
			Card testCard(suit, JACK);
			Assert::IsFalse(testCard == *card);
		}

		TEST_METHOD(greaterOperatorTest1)
		{
			Card testCard(suit, name);
			Assert::IsFalse(*card > testCard);
		}

		TEST_METHOD(greaterOperatorTest2)
		{
			Card testCard(DIAMONDS, name);
			Assert::IsFalse(*card > testCard);
		}

		TEST_METHOD(greaterOperatorTest3)
		{
			Card testCard(suit, JACK);
			Assert::IsFalse(*card > testCard);
		}

		TEST_METHOD(greaterOperatorTest4)
		{
			Card testCard(DIAMONDS, JACK);
			Assert::IsFalse(*card > testCard);
		}

		TEST_METHOD(greaterOperatorTest5)
		{
			Card testCard(suit, FIVE);
			Assert::IsTrue(*card > testCard);
		}

		TEST_METHOD(greaterOperatorTest6)
		{
			Card testCard(DIAMONDS, FIVE);
			Assert::IsTrue(*card > testCard);
		}

		~CardTests() {
			delete card;
		}
	};


	TEST_CLASS(HumanPlayerTest)
	{
	private:
		HumanPlayer* player;
		vector<Card*> playerCards;
	public:
		HumanPlayerTest() {
			player = new HumanPlayer;
			playerCards.push_back(new Card(HEARTS, TEN));
			playerCards.push_back(new Card(SPADES, TEN));
			playerCards.push_back(new Card(DIAMONDS, TEN));
			playerCards.push_back(new Card(HEARTS, JACK));
			playerCards.push_back(new Card(SPADES, JACK));

			for (auto card : playerCards)
				player->addCard(card);
		}

		TEST_METHOD(getCardsTest) {
			vector<Card*> cards = player->getCards();
			Assert::IsTrue(areEqual(cards, playerCards));
		}

		TEST_METHOD(addCardTest) {
			Card* newCard = new Card(SPADES, ACE);
			player->addCard(newCard);
			Assert::IsTrue(contains(player->getCards(), newCard));
		}

		TEST_METHOD(selectCardsForTurnTest1) {
			Card* cardToSelect = new Card(HEARTS, TEN);

			player->selectCardsForTurn(cardToSelect);
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.size() == 3);
			Assert::IsTrue(contains(selectedCards, cardToSelect));
			Assert::IsTrue(contains(selectedCards, new Card(SPADES, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
		}

		TEST_METHOD(selectCardsForTurnTest2) {
			vector<Card*> cardsToBeat = { new Card(SPADES, THREE) };
			Card* cardToSelect = new Card(HEARTS, TEN);

			player->setCardsToBeat(cardsToBeat);
			bool res = player->selectCardsForTurn(cardToSelect);
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(res);
			Assert::IsTrue(selectedCards.size() == 1);
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
		}

		TEST_METHOD(selectCardsForTurnTest3) {
			vector<Card*> cardsToBeat = { new Card(SPADES, TWO) };
			Card* cardToSelect = new Card(HEARTS, TEN);

			player->setCardsToBeat(cardsToBeat);
			bool res = player->selectCardsForTurn(cardToSelect);
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsFalse(res);
			Assert::IsTrue(selectedCards.empty());
		}

		TEST_METHOD(canFightBack1) {
			vector<Card*> cardsToBeat = { new Card(SPADES, TWO) };

			player->setCardsToBeat(cardsToBeat);
			
			Assert::IsFalse(player->canFightBack());
		}

		TEST_METHOD(canFightBack2) {
			vector<Card*> cardsToBeat = { new Card(SPADES, THREE) };

			player->setCardsToBeat(cardsToBeat);

			Assert::IsTrue(player->canFightBack());
		}

		TEST_METHOD(canFightBack3) {
			vector<Card*> cardsToBeat = { new Card(HEARTS, THREE), new Card(CLUBS, THREE), new Card(SPADES, THREE), new Card(DIAMONDS, THREE) };

			player->setCardsToBeat(cardsToBeat);

			Assert::IsFalse(player->canFightBack());
		}
		TEST_METHOD(makeTurnTest) {
			Card* cardToSelect = new Card(HEARTS, TEN);

			player->selectCardsForTurn(cardToSelect);
			vector<Card*> turnResult = player->makeTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.empty());
			Assert::IsTrue(turnResult.size() == 3);
			Assert::IsTrue(contains(turnResult, cardToSelect));
			Assert::IsTrue(contains(turnResult, new Card(SPADES, TEN)));
			Assert::IsTrue(contains(turnResult, new Card(DIAMONDS, TEN)));
		}

		~HumanPlayerTest() {
			delete player;
			for (auto card : playerCards)
				delete card;
		}
	};

	TEST_CLASS(AIPlayerTest)
	{
	private:
		AIPlayer* player;
		vector<Card*> playerCards;
	public:
		AIPlayerTest() {
			player = new AIPlayer;
			playerCards.push_back(new Card(HEARTS, TEN));
			playerCards.push_back(new Card(SPADES, TEN));
			playerCards.push_back(new Card(DIAMONDS, TEN));
			playerCards.push_back(new Card(HEARTS, JACK));
			playerCards.push_back(new Card(SPADES, JACK));

			for (auto card : playerCards)
				player->addCard(card);
		}

		TEST_METHOD(selectCardsForTurnTest) {
			player->selectCardsForTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.size() == 3);
			Assert::IsTrue(contains(selectedCards, new Card(HEARTS, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(SPADES, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
		}
		
		TEST_METHOD(makeMoveTest1) {
			vector<Card*> cardsToBeat = { new Card(HEARTS, THREE) };
			player->setCardsToBeat(cardsToBeat);
			player->selectCardsForTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.size() == 1);
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
		}

		TEST_METHOD(makeMoveTest2) {
			vector<Card*> cardsToBeat = { new Card(HEARTS, THREE), new Card(CLUBS, THREE) };
			player->setCardsToBeat(cardsToBeat);
			player->selectCardsForTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.size() == 2);
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(SPADES, TEN)));
		}

		TEST_METHOD(makeMoveTest3) {
			vector<Card*> cardsToBeat = { new Card(HEARTS, THREE), new Card(CLUBS, THREE), new Card(SPADES, THREE)};
			player->setCardsToBeat(cardsToBeat);
			player->selectCardsForTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.size() == 3);
			Assert::IsTrue(contains(selectedCards, new Card(HEARTS, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(SPADES, TEN)));
			Assert::IsTrue(contains(selectedCards, new Card(DIAMONDS, TEN)));
		}

		TEST_METHOD(makeMoveTest4) {
			vector<Card*> cardsToBeat = { new Card(HEARTS, THREE), new Card(CLUBS, THREE), new Card(SPADES, THREE), new Card(DIAMONDS, THREE) };
			player->setCardsToBeat(cardsToBeat);
			player->selectCardsForTurn();
			vector<Card*> selectedCards = player->getSelectedCards();

			Assert::IsTrue(selectedCards.empty());
		}

		~AIPlayerTest() {
			delete player;
			for (auto card : playerCards)
				delete card;
		}
	};
}
