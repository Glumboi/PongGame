#include "player.h"

void InitPlayer(Player *player, void *game)
{
    Location dfL = {10, GetScreenHeight() / 2 - PLAYER_HEIGHT};
    InitPlayerEx(player, game, dfL.x, dfL.y);
}

void InitPlayerEx(Player *player, void *game, int initX, int initY)
{
    if (!game)
        return;
    player->obj.name = "Player";
    player->obj.location.x = initX;
    player->obj.location.y = initY;
    player->obj.ObjectRender = RenderPlayer;
    player->obj.ObjectStart = StartPlayer;
    player->obj.isVisible = 1;
    player->obj.parentGame = game;
    GameAddGameObject((Game *)game, &player->obj);
}

void HandlePlayerMovement(GameObject *obj)
{
    // Movement
    if (IsKeyDown(KEY_W))
        obj->location.y -= 5;
    if (IsKeyDown(KEY_S))
        obj->location.y += 5;
}

void CheckPlayerScreenBounds(GameObject *obj)
{
    // Bounds checks
    if (obj->location.y < 0)
        obj->location.y = 0;
    if (obj->location.y > GetScreenHeight() - PLAYER_HEIGHT)
        obj->location.y = GetScreenHeight() - PLAYER_HEIGHT;
}

void RenderPlayer(GameObject *obj)
{
    HandlePlayerMovement(obj);
    CheckPlayerScreenBounds(obj);

    // Render
    if (obj->isVisible)
        DrawRoundedRectangle(obj->location.x, obj->location.y, PLAYER_WIDTH, PLAYER_HEIGHT, 10, WHITE);
}

void StartPlayer(GameObject *obj)
{
    printf("Player started!\n");
}
