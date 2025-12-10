#pragma once
#include <vector>
#include <iostream>
#include "raylib.h"

class Card
{
public:
	enum Rank
	{
		ace,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
		ten,
		jack,
		queen,
		king,
		max_ranks,
	};
	enum Suit
	{
		clubs,
		diamonds,
		hearts,
		spades,
		max_suits,
	};

	Rank m_rank;
	Suit m_suit;
	Rectangle mappedCard;
	char* text;
	Color color;
public:
	Card(Rank rank, Suit suit);

	int getValue() const;
	
	void Card_Render( Texture mappedTex, Vector2 pos, Color tint); //change texture to rectangle if needed
	friend std::ostream& operator<<(std::ostream& os, const Card& card); //use for debug if needed
};