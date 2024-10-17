#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "gameTypes.h"
#include "actors.h"
#include "customShapes.h"
#include "enemy.h"

#define ENEMY_HEIGHT 200
#define ENEMY_WIDTH 25

void InitEnemy(Enemy *enemy, void *game);
void InitEnemyEx(Enemy *enemy, void *game, int initX, int initY);

void HandleEnemyMovement(GameObject *obj);
void CheckEnemyScreenBounds(GameObject *obj);

void RenderEnemy(GameObject *obj);
void StartEnemy(GameObject *obj);

#endif