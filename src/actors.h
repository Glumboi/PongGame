#ifndef ACTORS_H
#define ACTORS_H

#include "gameTypes.h"

typedef struct player
{
    struct gameObject obj;
} Player;

typedef struct ball
{
    struct gameObject obj;
    struct player *player;
    int initLaunchDir;
    float velocityX;
    float velocityY;
    float speed;
    int score;
} Ball;

typedef struct scoreUi
{
    struct gameObject obj;
    struct ball *ball;
} ScoreUi;

#endif