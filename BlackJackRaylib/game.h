#pragma once
#include "player.h"
#include "dealer.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include "raygui.h"

class Game
{
    enum EndState
    {
        PlayerWon,
        DealerWon,
        Tie,
    };
    struct guiVars
    {
        Rectangle hitButtonBounds = {};
        Rectangle standButtonBounds = {};
    };
public://change to private later
    Deck deck;
    Player player;
    Dealer dealer;
    bool wonState = false; //siwtch statement in function for end statement hanlidng TODO rename to gameENd?
    EndState GameResult;
    guiVars gui;
    Texture2D cardTexture;
public:
    Game();
    ~Game();
    void Start();
    void Restart();
    void HandleInput();
    void InitButtons();
    void Algorithm();

    void AddPlayer();
    void AddDealer();

    void RenderMainMenu();
    void RenderEndScreen();
    void RenderHands();
    void RenderStats();
};


class Command
{
public:
  virtual ~Command() {}
  virtual void execute(Game &game) = 0;
};

class HitCommand : public Command
{
public:
    virtual void execute(Game &game)
    { 
        game.player.hit(game.deck); 
    }
};

class StandCommand : public Command
{
public:
    virtual void execute(Game &game)
    {
        game.player.stand();
    }
};

class InputHandler
{

public:
    InputHandler(Command* hitCommand, Command* standCommand)
        : hit(hitCommand), stand(standCommand) 
    {
    }
  void handleInput(Game &game, Vector2 mouse, Rectangle hitButton, Rectangle standButton)
  {
    if (CheckCollisionPointRec(mouse, hitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {hit->execute(game);}
    else if(CheckCollisionPointRec(mouse, standButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {stand->execute(game);}
  }
private:
    Command* hit;
    Command* stand;
};
