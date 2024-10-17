#include "gameTypes.h"

void InitGameObject(GameObject *outObj, void *game)
{
    InitGameObjectEx(outObj, game, 0, 0);
}

void InitGameObjectEx(GameObject *outObj, void *game, int initX, int initY)
{
    VALID_PTR(outObj);
    
    outObj->location.x = initX;
    outObj->location.y = initY;
    outObj->ObjectRender = RenderGameObject;
    outObj->ObjectStart = StartGameObject;
    outObj->isVisible = 1;

    if (game)
        outObj->parentGame = game;
}

void RenderGameObject(GameObject *obj)
{
    if (obj->isVisible)
        DrawRectangle(obj->location.x, obj->location.y, 50, 100, WHITE);
}

void StartGameObject(GameObject *obj)
{
    // Do nothing, each object has to add functionality manually
}
