#include "Deck.h"
#include <random>

const std::vector<std::string> rank_txt = { 
    "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
const std::vector<std::string> suit_txt = { "Hearts", "Diamonds", "Spades", "Clubs" };

//DEBUG
// std::ostream& operator<<(std::ostream& os, const Card& card)
// {
// 	if (card.m_rank >= 0 && card.m_rank < rank_txt.size() &&
// 		card.m_suit >= 0 && card.m_suit < suit_txt.size())
// 	{
// 		os << rank_txt[card.m_rank] << " of " << suit_txt[card.m_suit] << ' ';
// 	}
// 	else
// 	{
// 		os << "Invalid Card\n";
// 	}
//     return os;
// }

void Deck::initDeck()
{
	deck.clear();
	for (int i = 0; i < Card::max_suits; i++)
	{
		for (int j = 0; j < Card::max_ranks; j++)
		{
			deck.push_back({ Card{static_cast<Card::Rank>(j),static_cast<Card::Suit>(i)} });
		}
	}
}
void Deck::shuffle()
{
	std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(deck.begin(), deck.end(), g);
}
//DEBUG
// void Deck::print()
// {
// 	if (!isEmpty())
// 	{
// 		for (const auto& card : deck)
// 		{
// 			std::cout << card;
// 		}
// 	}

// }
Card Deck::getCard()
{
	if (deck.empty())
	{
		std::cerr <<"No more cards in the deck.";
		std::exit(1);
		//throw std::runtime_error("No more cards in the deck."); TODO: implement exceptions
	}
	Card temp = deck.front();
	deck.erase(deck.begin());
	return temp;
}
bool Deck::isEmpty()
{
	if (deck.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Deck::getSize()
{
    return deck.size();
}
