#ifndef PONGBALL_H
#define PONGBALL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <raylib.h>
#include <math.h>

#include "../engineCore/scene.h"
#include "../engineCore/engineTypes.h"
#include "../engineCore/gameObject.h"

#include "player.h"

#define BALL_SIZE 10
#define BALL_SPEED 400.0f
#define WINDOW_WIDTH_SPEED_MULTIPLIER 500

typedef struct pongBall
{
    GameObject obj;

    int initLaunchDir;
    float velocityX;
    float velocityY;
    float moveSpeed;

    GameObject *player;
    GameObject *player2;

    Player *lastHittingPlayer;
} PongBall;

// Standard functions

void PongBall_Init(PongBall *ball);

void PongBall_OnStart(GameObject *obj);
void PongBall_OnUpdate(GameObject *obj);

// Custom functions

void PongBall_Reset(GameObject *obj);
void PongBall_CollisionChecks(GameObject *ball, GameObject *targetObject);

#endif