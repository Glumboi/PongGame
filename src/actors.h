#ifndef ACTORS_H
#define ACTORS_H

#include "gameTypes.h"

#define SCORE_OFFSET_TOP 25
#define ENEMY_SCORE_OFFSET_LEFT 75

typedef struct scoreObject
{
    struct gameObject obj;
    int score;
} BallAware;

typedef struct player
{
    struct scoreObject scoreObject;
} Player;

typedef struct enemy
{
    struct scoreObject scoreObject;
} Enemy;

typedef struct ball
{
    struct gameObject obj;
    struct player *player;
    struct enemy *enemy;
    int initLaunchDir;
    float velocityX;
    float velocityY;
    float speed;
} Ball;

typedef struct scoreUi
{
    struct gameObject obj;
    struct ball *ball;
} ScoreUi;

#endif