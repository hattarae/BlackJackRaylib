#pragma once
#include "Deck.h"

class Person
{
	std::vector<Card> m_hand{};

public:
	Person() 
	{
		
	}
	bool playing;
	int score = 0;
	bool won = false;
	void hit(Deck &deck);
	void ignoreLine();
	bool clearFailedExtraction();
	int checkHand();
	void printHand(Texture mappedTex, Vector2 startPos, Color tint);
	void dealInitialHand(Deck &deck);
};