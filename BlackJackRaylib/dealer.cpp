#include "dealer.h"
#define DEALER_DRAW_MAX 17
void Dealer::Distribute()
{
}
void Dealer::DealerDrawCards(Deck& deck)
{
	while(score < DEALER_DRAW_MAX)
    {
        hit(deck);
        score = checkHand();
    }
    score = checkHand();
}