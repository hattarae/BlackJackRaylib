#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include"raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

double lastUpdateTime = 0;
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}


int main()
{
    const int screenWidth = 700;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Card Test");

    Texture2D cardTexture = LoadTexture("cards1.png"); 
    //- check size before making custom,and make smaller cards change in cardRender

    Game testGame;
    testGame.Start();
    
    printf("Texture size: %d x %d\n", cardTexture.width, cardTexture.height);
    while (!WindowShouldClose())
    {
        if (EventTriggered(0.9))
        {
            std::cout << "DEBUG Player score: " << testGame.player.score <<'\n';
            std::cout << "DEBUG Dealer score: " << testGame.dealer.score <<'\n';
        }
        BeginDrawing();
        
        ClearBackground(BLACK);
        
            testGame.Algorithm();
            testGame.HandleInput();
            testGame.InitButtons();
            testGame.RenderHands();
            testGame.RenderStats();
            //testGame.Start();
            if (testGame.wonState) 
            {
                testGame.RenderEndScreen(); 
            }


        EndDrawing();
    }
    //card tesxture unloaded in game destructor
    CloseWindow();

    return 0;
}
