#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdio.h>

#include "../engineCore/gameObject.h"

#include "playerShared.h"

void Player_Init(struct player *player);

void Player_OnStart(GameObject *obj);
void Player_OnUpdate(GameObject *obj);

#endif
