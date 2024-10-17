#include "game.h"

void InitGame(Game *outGame, WindowData *windowData)
{
    if (!windowData)
        return;

    SetConfigFlags(windowData->flags);
    InitWindow(windowData->w, windowData->h, windowData->title);

    if (!outGame->objectPool.rawMem)
    {
        printf("Failed to allocate memory for game object pool.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize objects
    for (size_t i = 0; i < outGame->objectPool.head.len; i++)
    {
        outGame->objectPool.rawMem[i]->name = NULL; // Set name as NULL
        outGame->objectPool.rawMem[i]->ObjectRender = NULL;
        outGame->objectPool.rawMem[i]->ObjectStart = NULL;
        outGame->objectPool.rawMem[i]->parentGame = outGame; // Set parent game
    }
}

void StartGame(Game *game)
{
    VALID_PTR(game);
    srand(time(NULL)); // Initialize random seed

    for (size_t i = 0; i < game->objectPool.head.len; i++)
    {
        GameObject *obj = game->objectPool.rawMem[i];
        if (obj->ObjectStart)
            obj->ObjectStart(obj);
    }
}
void GameAddGameObject(Game *game, GameObject *gameObject)
{
    VALID_PTR(game);
    VALID_PTR(gameObject);
    G_VECTOR_PUSH_BACK(GameObject *, game->objectPool, gameObject);
}

int FindGameObject(Game *g, GameObject **outObj, const char *name)
{
    if (!g || !name)
    {
        printf("Error: Invalid pointer in FindGameObject\n");
        return 0;
    }

    for (size_t i = 0; i < g->objectPool.head.len; i++) // Use ptr, not len
    {

        if (g->objectPool.rawMem[i]->name && strcmp(g->objectPool.rawMem[i]->name, name) == 0)
        {
            *outObj = g->objectPool.rawMem[i];
            return 1;
        }
    }

    printf("Warning: GameObject with name '%s' not found\n", name);
    return 0;
}

void GameRender(Game *game)
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (size_t i = 0; i < game->objectPool.head.len; i++)
    {
        GameObject *obj = game->objectPool.rawMem[i];
        if (obj->ObjectRender && obj)
            obj->ObjectRender(obj);
    }

    EndDrawing();
}
