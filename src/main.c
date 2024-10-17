#include <stdio.h>
#include "../include/raylib.h"
#include "game.h"
#include "gameTypes.h"
#include "player.h"
#include "enemy.h"
#include "ball.h"
#include "scoreUi.h"

int WinMain(int argc, char const *argv[])
{
    WindowData wData = {"Pong game", 800, 600, FLAG_WINDOW_RESIZABLE};

    Game g;
    InitGame(&g, &wData);

    Player p;
    InitPlayer(&p, &g);

    Enemy e;
    InitEnemy(&e, &g);

    Ball b;
    InitBall(&b, &g);

    //ScoreUi ui;
    //InitScoreUi(&ui, &g);

    StartGame(&g);

    while (!WindowShouldClose())
    {
        GameRender(&g);
    }

    return 0;
}
