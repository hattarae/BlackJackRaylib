#include "game.h"
#define _CRT_SECURE_NO_WARNINGS
#define SCREEN_WIDTH GetScreenWidth()
#define SCREEN_HEIGHT GetScreenHeight()

#define BLACKJACK 21
#define BURST 21

#define BUTTON_WIDTH  120
#define BUTTON_HEIGHT 30

#define FONT_SIZE 38
#define FONT_SPACING  2


Game::Game() : deck(), player(), dealer()
{
	player.playing = true;
	dealer.playing = false;
	cardTexture = LoadTexture("cards1.png");
}

Game::~Game() // TODO: start new game when restarted or resuse single Game object??-(save game?)
{
	UnloadTexture(cardTexture);
}

void Game::Start()
{
	deck.initDeck();
	std::cout << "Deck size after init: " << deck.getSize() << std::endl; // Add this
	deck.shuffle();
	player.dealInitialHand(this->deck);
	dealer.dealInitialHand(this->deck);
	player.score = player.checkHand(); //why score needs to be checked here again when checked in constructor??idk
	dealer.score = dealer.checkHand();
	deck.shuffle();


}

void Game::Restart()
{
	deck.initDeck();
	deck.shuffle();
	player.score = 0;
	dealer.score = 0;
	player.won = false;
	dealer.won = false;
}

void Game::HandleInput() //command pattern used
{
	Vector2 mouse = GetMousePosition();

	HitCommand* hitCmd = new HitCommand();
	StandCommand* standCmd = new StandCommand();
	InputHandler inputHandler(hitCmd, standCmd);

	if (player.allowPlayerInput == true)
	{
		if (CheckCollisionPointRec(mouse, gui.hitButtonBounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			std::cout << "DEBUG: PLayer Hit button pressed!\n";
			hitCmd->execute(*this);
			player.score = player.checkHand();
			std::cout << "DEBUG player score: " << player.score << '\n';
		}
	}

	if (CheckCollisionPointRec(mouse, gui.standButtonBounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		std::cout << "DEBUG: Player Stand button pressed!\n";
		standCmd->execute(*this);
		dealer.playing = true;

	}

}

void Game::InitButtons() // this is gui use to create buttons on screen
{
	gui.hitButtonBounds = { float(SCREEN_WIDTH-200), float(SCREEN_HEIGHT-50), BUTTON_WIDTH, BUTTON_HEIGHT };
	gui.standButtonBounds = { float(SCREEN_WIDTH-200), float(SCREEN_HEIGHT-100), BUTTON_WIDTH, BUTTON_HEIGHT };
	GuiButton(gui.hitButtonBounds, "HIT(player)");
    GuiButton(gui.standButtonBounds, "STAND(player)");
}

void Game::Algorithm()
{
	int playerTotal = player.score;
	int dealerTotal = dealer.score;
	bool playerBust = playerTotal > BURST;
	bool dealerBust = dealerTotal > BURST;

	bool playerTurnOver = player.allowPlayerInput == false || playerBust;

	bool playerBlackjack = player.score == BLACKJACK;
	bool dealerBlackjack = dealer.score == BLACKJACK;

	if (playerBlackjack || dealerBlackjack) // check in cases of blackjack (score == 21)
	{
		player.allowPlayerInput = false;
		dealer.playing = false;

		if (playerBlackjack && dealerBlackjack)
		{
			std::cout << "DEBUG Result: Both won blackjack: TIE" << std::endl;
			wonState = true;
			GameResult = Tie;
			return;
		}
		else if (playerBlackjack)
		{
			std::cout << "DEBUG Result: Player won blackjack" << std::endl;
			player.won = true;
			wonState = true;
			GameResult = PlayerWon;
			return;
		}
		else if (dealerBlackjack)
		{
			std::cout << "DEBUG Result: Dealer won blackjack" << std::endl;
			dealer.won = true;
			wonState = true;
			GameResult = DealerWon;
			return;
		}
		return;
	}

	if (dealer.playing && !player.allowPlayerInput && player.playing == false)
	{
		dealer.DealerDrawCards(this->deck);
		player.allowPlayerInput = true;
		dealer.playing = false;
	}

	if (wonState == false && player.won == false && dealer.won == false) //game just started
	{
		if (playerBust)
		{
			//std::cout << "DEBUG player burst!\n";
			player.won = false;
			player.allowPlayerInput = false;
			player.playing = false;
			dealer.won = true;
			wonState = true;
			GameResult = DealerWon;
			return;
		}
		else if (dealerBust)
		{
			//std::cout << "DEBUG DEALER burst!\n";
			player.won = true;
			player.allowPlayerInput = false;
			player.playing = false;
			dealer.won = false;
			wonState = true;
			GameResult = PlayerWon;
			return;
		}

		if (player.playing == false && dealer.playing == false && playerTotal > dealerTotal ) 
		{
			dealer.won = false;
			player.won = true;
			wonState = true;
			GameResult = PlayerWon;
			return;
		}
		else if(player.playing == false && dealer.playing == false && playerTotal < dealerTotal  )
		{
			dealer.won = true;
			player.won = false;
			wonState = true;
			GameResult = DealerWon;
			return;
		}
		else if ((playerTotal != 0 && dealerTotal != 0) && (playerTotal == dealerTotal) && player.playing == false && dealer.playing == false)
		{
			//std::cout << "DEBUG Result: TIE" << std::endl;
			wonState = true;
			GameResult = Tie;
			return;
		}
		return;
	}


}

void Game::RenderMainMenu()
{
	DrawRectangleRec({0, 0, float(SCREEN_WIDTH), float(SCREEN_HEIGHT)}, RED);
	DrawTextEx(GetFontDefault(), "MAIN MENU", {300, 250}, 38, 2, GREEN);
}

void Game::RenderEndScreen()
{
	const char* text = nullptr;
	switch (GameResult)
	{
	case Tie:
		text = "TIE";
		break;
	case PlayerWon:
		text = "PLAYER WON";
		break;
	case DealerWon:
		text = "DEALER WON";
		break;
	default:
		break;
	}
	 Vector2 textSize = MeasureTextEx(GetFontDefault(), text, FONT_SIZE, FONT_SPACING);
	//std::cout << "DEBUG: RenderEndScreen called, wonState = " << wonState << "\n";
	if (wonState == true)
	{
		DrawRectangleRec({0, 0,float(SCREEN_WIDTH), float(SCREEN_HEIGHT)}, WHITE);
		DrawTextEx(GetFontDefault(), text, { SCREEN_WIDTH/2 - textSize.x/2, GetScreenHeight()/2 - textSize.y/2 }, FONT_SIZE, FONT_SPACING, BLACK);
		//KEEP THIS JUST IN CASE SOMETHING BREAKS 
		// switch (GameResult)
		// {
		// case Tie:
		// 	DrawTextEx(GetFontDefault(), "TIE", {300, 250}, FONT_SIZE, FONT_SPACING, BLACK);
		// 	break;
		// case PlayerWon:
		// 	DrawTextEx(GetFontDefault(), "PLAYER WON", {300, 250}, FONT_SIZE, 2, BLACK);
		// 	break;
		// case DealerWon:
		// 	DrawTextEx(GetFontDefault(), "DEALER WON", {300, 250}, 38, 2, BLACK);
		// 	break;
		// }
	}
}

void Game::RenderHands()
{
	player.printHand(cardTexture,{100,100},WHITE);
	dealer.printHand(cardTexture,{100,300},WHITE);
}

void Game::RenderStats()
{
	char playerScoreString[10];
	sprintf_s(playerScoreString, "%d", player.score);
	DrawTextEx(GetFontDefault(), playerScoreString, {400, 300}, 38, 2, RED);
	char dealerScoreString[10];
	sprintf_s(dealerScoreString, "%d", dealer.score);
	DrawTextEx(GetFontDefault(), dealerScoreString, {400, 360}, 38, 2, RED);
}


// delete bottom two i guess theyre intialized already in game constructor; unless more players per session added in future
void Game::AddPlayer()
{
}

void Game::AddDealer()
{
}

