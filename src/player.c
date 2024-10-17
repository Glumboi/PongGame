#include "player.h"

void InitPlayer(Player *player, Game *game)
{
    Location dfL = {10, GetScreenHeight() / 2 - PLAYER_HEIGHT};
    InitPlayerEx(player, game, dfL.x, dfL.y);
}

void InitPlayerEx(Player *player, Game *game, int initX, int initY)
{
    if (!game)
        return;
    player->scoreObject.obj.name = "Player";
    player->scoreObject.obj.location.x = initX;
    player->scoreObject.obj.location.y = initY;
    player->scoreObject.obj.ObjectRender = RenderPlayer;
    player->scoreObject.obj.ObjectStart = StartPlayer;
    player->scoreObject.obj.isVisible = 1;
    player->scoreObject.obj.parentGame = game;
    player->scoreObject.score = 0;
    GameAddGameObject(game, &player->scoreObject.obj);
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
    if (player->scoreObject.obj.isVisible)
    {
        DrawRoundedRectangle(player->scoreObject.obj.location.x, player->scoreObject.obj.location.y, PLAYER_WIDTH, PLAYER_HEIGHT, 10, WHITE);
        DrawText(TextFormat("Score: %d", player->scoreObject.score),
                 player->scoreObject.obj.location.x,
                 player->scoreObject.obj.location.y - SCORE_OFFSET_TOP, 24, WHITE);
    }
}

void StartPlayer(GameObject *obj)
{
    printf("Player started!\n");
}
