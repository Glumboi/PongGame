#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "gameTypes.h"
#include "actors.h"
#include "customShapes.h"

#define PLAYER_HEIGHT 200
#define PLAYER_WIDTH 25

void InitPlayer(Player *player, void *game);
void InitPlayerEx(Player *player, void *game, int initX, int initY);

void HandlePlayerMovement(GameObject *obj);
void CheckPlayerScreenBounds(GameObject *obj);

void RenderPlayer(GameObject *obj);
void StartPlayer(GameObject *obj);

#endif