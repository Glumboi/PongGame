#ifndef ENGINEWINDOW_H
#define ENGINEWINDOW_H

#include <raylib.h>
#include "scene.h"

typedef struct engineWindow
{
    int w, h;
    unsigned int flags;
    char *title;
    Scene currentScene;
} EngineWindow;

void EngineWindow_Init(EngineWindow *window, int w, int h, char *title, unsigned int flags);
void EingineWindow_RunMainLoop(EngineWindow *window);
void EngineWindow_SetScene(EngineWindow *window, Scene *scene);

#endif