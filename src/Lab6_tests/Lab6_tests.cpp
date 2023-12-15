#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab6_code/Cards.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab6tests
{
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
}
