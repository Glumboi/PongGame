#include "player.h"

void Player_Init(Player *player)
{
    if (!player)
        return;
    player->obj = GameObject_NewName("Player1");
    player->obj.OnStart = Player_OnStart;
    player->obj.OnUpdate = Player_OnUpdate;
    player->obj.location = (Location){10, GetScreenHeight() / 2 - PLAYER_HEIGHT};
    player->score = 0;
    player->moveSpeed = PLAYER_SPEED;
}

void Player_OnUpdate(GameObject *obj)
{
    Player_HandleMovement(obj, KEY_W, KEY_S);

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
                 obj->location.x,
                 obj->location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}
