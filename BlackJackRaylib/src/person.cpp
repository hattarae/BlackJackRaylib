#include "Person.h"
#include "Deck.h"
#include <iostream>
#include <string>

void Person::hit(Deck& deck)
{
	m_hand.push_back(deck.getCard());
}
int Person::checkHand()
{
    int value = 0;
    int aceCount = 0;
    for (auto& card : m_hand)
    {
        int cardVal = card.getValue();
        value += cardVal;
        if (card.m_rank == Card::ace)
            aceCount++;
    }
    while (value > 21 && aceCount > 0)
    {
        value -= 10;
        aceCount--;
    }
    return value;
}

void Person::printHand(Texture mappedTex, Vector2 startPos, Color tint) //fix not to print every render call, see card.cpp
{
    Vector2 pos = startPos;
    for (auto& card : m_hand)
    {
        card.Card_Render(mappedTex, pos, tint);
        pos.x += 100; // Move next card 100 pixels to the right
    }
}

void Person::dealInitialHand(Deck &deck)
{
    m_hand.clear();
    m_hand.push_back(deck.getCard());
    m_hand.push_back(deck.getCard());
}