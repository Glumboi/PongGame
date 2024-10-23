#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>

#include "../engineCore/gameObject.h"

#include "playerShared.h"

#define ENEMY_SCORE_OFFSET_LEFT 75

void Enemy_Init(Player *enemy);

void Enemy_OnStart(GameObject *obj);
void Enemy_OnUpdate(GameObject *obj);

#endif