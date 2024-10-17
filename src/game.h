#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "actors.h"
#include <time.h>
#include "gameTypes.h"
#include "actors.h"

typedef struct windowData
{
    char *title;
    int w, h, flags;
} WindowData;

typedef struct game
{
    struct gameObjectPool_t objectPool;
} Game;

void InitGame(Game *outGame, WindowData *windowData);
void StartGame(Game *game);

void GameAddGameObject(Game *game, GameObject *gameObject);
int FindGameObject(Game *g, GameObject **outObj, const char *name);
void GameRender(Game *game);

#endif