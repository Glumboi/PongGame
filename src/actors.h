#ifndef ACTORS_H
#define ACTORS_H

#include "gameTypes.h"

#define SCORE_OFFSET_TOP 25
#define ENEMY_SCORE_OFFSET_LEFT 75

typedef struct ballAware
{
    struct gameObject obj;
    int score;
} BallAware;

typedef struct player
{
    struct ballAware ballAware;
} Player;

typedef struct enemy
{
    struct ballAware ballAware;
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
    int score;
} Ball;

typedef struct scoreUi
{
    struct gameObject obj;
    struct ball *ball;
} ScoreUi;

#endif