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
    player->ballAware.obj.name = "Player";
    player->ballAware.obj.location.x = initX;
    player->ballAware.obj.location.y = initY;
    player->ballAware.obj.ObjectRender = RenderPlayer;
    player->ballAware.obj.ObjectStart = StartPlayer;
    player->ballAware.obj.isVisible = 1;
    player->ballAware.obj.parentGame = game;
    player->ballAware.score = 0;
    GameAddGameObject((Game *)game, &player->ballAware.obj);
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
    Player *player = (Player *)obj;
    if (player->ballAware.obj.isVisible)
    {
        DrawRoundedRectangle(player->ballAware.obj.location.x, player->ballAware.obj.location.y, PLAYER_WIDTH, PLAYER_HEIGHT, 10, WHITE);
        DrawText(TextFormat("Score: %d", player->ballAware.score),
                 player->ballAware.obj.location.x,
                 player->ballAware.obj.location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}

void StartPlayer(GameObject *obj)
{
    printf("Player started!\n");
}
