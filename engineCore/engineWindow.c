#include "engineWindow.h"

void EngineWindow_Init(EngineWindow *window, int w, int h, char *title, unsigned int flags)
{
    if (!window)
        return;

    window->w = w;
    window->h = h;
    window->title = title;
    window->flags = flags;
    
    SetConfigFlags(window->flags);
    InitWindow(window->w, window->h, window->title);
}

void EingineWindow_RunMainLoop(EngineWindow *window)
{
    if (!window)
        return;

    window->currentScene.OnStart(&window->currentScene);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        window->currentScene.OnUpdate(&window->currentScene);
        EndDrawing();
    }

    window->currentScene.OnDestroy(&window->currentScene);
}

void EngineWindow_SetScene(EngineWindow *window, Scene *scene)
{
    if (!window || !scene)
        return;
    window->currentScene = *scene;
}
