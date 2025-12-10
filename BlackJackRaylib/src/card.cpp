#include "card.h"

Card::Card(Rank rank, Suit suit) : m_rank{rank}, m_suit{suit}
{
	const int cardWidth = 96;
	const int cardHeight = 192;

	mappedCard =
	{
    static_cast<float>(suit) * cardWidth,
    static_cast<float>(rank) * cardHeight,
    static_cast<float>(cardWidth),
    static_cast<float>(cardHeight)
	};
	color = WHITE;
}
int Card::getValue() const
{
	switch (m_rank)
	{
	case ace:
		return 11;
	case two:
		return 2;
	case three:
		return 3;
	case four:
		return 4;
	case five:
		return 5;
	case six:
		return 6;
	case seven:
		return 7;
	case eight:
		return 8;
	case nine:
		return 9;
	case ten:
		return 10;
	case jack:
		return 10;
	case queen:
		return 10;
	case king:
		return 10;
	default:
		return 0;
	}
}

void Card::Card_Render( Texture mappedTex, Vector2 pos, Color tint)
{
	int value = getValue();
	DrawTextureRec(mappedTex, mappedCard, pos, tint);

	const char *cardText = NULL;
	Vector2 textSize = {0};
	Vector2 textPos = {0};


	switch (m_rank)
	{
	case ace:
		cardText = "ACE";
		break;
	case jack:
		cardText = "J";
		break;
	case king:
		cardText = "K";
		break;
	case queen:
		cardText = "Q";
		break;
	default:
		cardText = TextFormat("%d", value);
		break;
	}

	textSize = MeasureTextEx(GetFontDefault(), cardText, 32, 4);
	textPos = {
		pos.x + (mappedCard.width - textSize.x) / 2,
		pos.y + (mappedCard.height - textSize.y) / 2};
	DrawTextEx(GetFontDefault(), cardText, textPos, 32, 4, RED);
}
//DEBUG
// std::ostream& operator<<(std::ostream& os, const Card& card)
// {
//     // Example: print rank and suit as numbers
//     os << "[" << static_cast<int>(card.m_rank) << "," << static_cast<int>(card.m_suit) << "]";
//     return os;
// }