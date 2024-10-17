#include "scoreUi.h"

void InitScoreUi(ScoreUi *ui, void *game)
{
    if (!game)
        return;
    InitScoreUiEx(ui, game, 10, 10);
}

void InitScoreUiEx(ScoreUi *ui, void *game, int initX, int initY)
{
    if (!game)
        return;

    ui->obj.isVisible = 1;
    ui->obj.location.x = initX;
    ui->obj.location.y = initY;
    ui->obj.name = "UI";
    ui->obj.ObjectRender = RenderScoreUi;
    ui->obj.ObjectStart = StartScoreUi;
    ui->obj.parentGame = game;

    GameAddGameObject((Game *)game, &ui->obj);
    GameObject *b;
    if (FindGameObject(game, &b, "Ball"))
    {
        ui->ball = (Ball *)b;
    }
}

void RenderScoreUi(GameObject *obj)
{
    ScoreUi* ui = (ScoreUi*)obj;
    if (ui->obj.isVisible)
        DrawText(TextFormat("Score: %d", ui->ball->score), obj->location.x, obj->location.y, 24, WHITE);
}

void StartScoreUi(GameObject *obj)
{
    printf("UI started!\n");
}
