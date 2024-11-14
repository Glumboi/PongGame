#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include <stdio.h>

#include "../engineCore/gameObject.h"

#include "playerShared.h"

#define ENEMY_SCORE_OFFSET_LEFT 75

void Enemy_Init(Player *player2);

void Enemy_OnStart(GameObject *obj);
void Enemy_OnUpdate(GameObject *obj);

#endif