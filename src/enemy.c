#include "enemy.h"

void Enemy_Init(Player *enemy)
{
    if (!enemy)
        return;

    enemy->score = 0;
    enemy->obj = GameObject_NewName("Player2");
    enemy->obj.OnStart = Enemy_OnStart;
    enemy->obj.OnUpdate = Enemy_OnUpdate;
    enemy->obj.location = (Location){GetScreenWidth() - 35, GetScreenHeight() / 2 - PLAYER_HEIGHT};
}

void Enemy_OnStart(GameObject *obj)
{
    printf("Enemy started!\n");
}

void Enemy_OnUpdate(GameObject *obj)
{
    Player_HandleMovement(obj, KEY_UP, KEY_DOWN);
    
    // Set enemy to right screen bounds
    obj->location.x = GetScreenWidth() - 35;

    Player *player = (Player *)obj;
    if (obj->isVisible)
    {
        DrawRoundedRectangle(
            obj->location.x,
            obj->location.y,
            PLAYER_WIDTH,
            PLAYER_HEIGHT,
            10,
            WHITE);

        DrawText(TextFormat("Score: %d", player->score),
                 obj->location.x - ENEMY_SCORE_OFFSET_LEFT,
                 obj->location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}
