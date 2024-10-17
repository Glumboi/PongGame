#include "enemy.h"

void InitEnemy(Enemy *enemy, void *game)
{
    Location dfL = {GetScreenWidth() - 35, GetScreenHeight() / 2 - ENEMY_HEIGHT};
    InitEnemyEx(enemy, game, dfL.x, dfL.y);
}

void InitEnemyEx(Enemy *enemy, void *game, int initX, int initY)
{
    if (!game)
        return;
    enemy->scoreObject.obj.name = "Enemy";
    enemy->scoreObject.obj.location.x = initX;
    enemy->scoreObject.obj.location.y = initY;
    enemy->scoreObject.obj.ObjectRender = RenderEnemy;
    enemy->scoreObject.obj.ObjectStart = StartEnemy;
    enemy->scoreObject.obj.isVisible = 1;
    enemy->scoreObject.obj.parentGame = game;
    enemy->scoreObject.score = 0;

    GameAddGameObject((Game *)game, &enemy->scoreObject.obj);
}

void HandleEnemyMovement(GameObject *obj)
{
    // Movement
    if (IsKeyDown(KEY_UP))
        obj->location.y -= 5;
    if (IsKeyDown(KEY_DOWN))
        obj->location.y += 5;

    obj->location.x = GetScreenWidth() - 35;
}

void CheckEnemyScreenBounds(GameObject *obj)
{
    // Bounds checks
    if (obj->location.y < 0)
        obj->location.y = 0;
    if (obj->location.y > GetScreenHeight() - ENEMY_HEIGHT)
        obj->location.y = GetScreenHeight() - ENEMY_HEIGHT;
}

void RenderEnemy(GameObject *obj)
{
    HandleEnemyMovement(obj);
    CheckEnemyScreenBounds(obj);

    Enemy *enemy = (Enemy *)obj;
    if (enemy->scoreObject.obj.isVisible)
    {
        DrawRoundedRectangle(enemy->scoreObject.obj.location.x, enemy->scoreObject.obj.location.y, ENEMY_WIDTH, ENEMY_HEIGHT, 10, WHITE);
        DrawText(TextFormat("Score: %d", enemy->scoreObject.score),
                 enemy->scoreObject.obj.location.x - ENEMY_SCORE_OFFSET_LEFT,
                 enemy->scoreObject.obj.location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}

void StartEnemy(GameObject *obj)
{
    printf("Enemy started!\n");
}
