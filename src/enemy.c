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
    enemy->ballAware.obj.name = "Enemy";
    enemy->ballAware.obj.location.x = initX;
    enemy->ballAware.obj.location.y = initY;
    enemy->ballAware.obj.ObjectRender = RenderEnemy;
    enemy->ballAware.obj.ObjectStart = StartEnemy;
    enemy->ballAware.obj.isVisible = 1;
    enemy->ballAware.obj.parentGame = game;
    enemy->ballAware.score = 0;

    GameAddGameObject((Game *)game, &enemy->ballAware.obj);
}

void HandleEnemyMovement(GameObject *obj)
{
    // Movement
    if (IsKeyDown(KEY_UP))
        obj->location.y -= 5;
    if (IsKeyDown(KEY_DOWN))
        obj->location.y += 5;
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
    if (enemy->ballAware.obj.isVisible)
    {
        DrawRoundedRectangle(enemy->ballAware.obj.location.x, enemy->ballAware.obj.location.y, ENEMY_WIDTH, ENEMY_HEIGHT, 10, WHITE);
        DrawText(TextFormat("Score: %d", enemy->ballAware.score), 
        enemy->ballAware.obj.location.x - ENEMY_SCORE_OFFSET_LEFT, 
        enemy->ballAware.obj.location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}

void StartEnemy(GameObject *obj)
{
    printf("Enemy started!\n");
}
