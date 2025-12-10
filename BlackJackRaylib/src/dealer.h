#pragma once
#include "person.h"

class Dealer : public Person
{
public:
    Dealer() : Person() 
    {
        score = checkHand();
    }
    void Distribute();
    void DealerDrawCards(Deck& deck);
};