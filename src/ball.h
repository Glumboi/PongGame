#ifndef BALL_H
#define BALL_H

#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include "game.h"
#include "gameTypes.h"
#include "actors.h"
#include "player.h"

#define BALL_SIZE 10
#define BALL_SPEED 2.5f

void InitBall(Ball *ball, void *game);
void InitBallEx(Ball *ball, void *game, int initX, int initY);

void RenderBall(GameObject *obj);
void StartBall(GameObject *obj);
void ResetBall(GameObject *obj);

void CheckBallPlayerCollision(Ball *ball, BallAware *ballAware);

#endif