#include <stdio.h>
#include <raylib.h>

#include "../engineCore/engineWindow.h"
#include "../engineCore/gameObject.h"
#include "../engineCore/scene.h"

#include "pongBall.h"
#include "player.h"
#include "enemy.h"

void RenderField(GameObject *obj)
{
    Vector2 start = {.x = GetScreenWidth() / 2, .y = 0};
    Vector2 end = {.x = GetScreenWidth() / 2, .y = GetScreenHeight()};
    DrawLineEx(start, end, 10, WHITE);

    // Player 1 side
    DrawRectangle(0, 0, GetScreenWidth() / 2, GetScreenHeight(), PINK);
}

int main(int argc, char const *argv[])
{
    EngineWindow w;
    EngineWindow_Init(&w, 800, 600, "Pong", FLAG_WINDOW_RESIZABLE);

    Scene s;
    Scene_Create(&s, "Scene1");

    GameObject field = GameObject_NewName("Field");
    field.OnUpdate = RenderField;
    Scene_AddGameObject(&s, &field);

    PongBall ball;
    PongBall_Init(&ball);
    Scene_AddGameObject(&s, &ball.obj);

    Player p;
    Player_Init(&p);
    Scene_AddGameObject(&s, &p.obj);

    Player p2;
    Enemy_Init(&p2);
    Scene_AddGameObject(&s, &p2.obj);

    EngineWindow_SetScene(&w, &s);
    EingineWindow_RunMainLoop(&w);

    return 0;
}
