#ifndef SCORE_UI_H
#define SCORE_UI_H

#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "gameTypes.h"
#include "actors.h"
#include "ball.h"

void InitScoreUi(ScoreUi *ui, void *game);
void InitScoreUiEx(ScoreUi *ui, void *game, int initX, int initY);

void RenderScoreUi(GameObject *obj);
void StartScoreUi(GameObject *obj);

#endif