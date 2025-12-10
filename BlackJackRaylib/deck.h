#pragma once
#include <vector>
#include <iostream>
#include <algorithm> // For std::random_shuffle
#include <map>
#include <random>
#include "card.h"

class Deck
{
private:
    std::vector<Card> deck{};

public:
    void initDeck();
    void shuffle();
    //void print();
    Card getCard();
    bool isEmpty();
    int getSize();

};