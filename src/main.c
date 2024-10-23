#include <stdio.h>
#include <raylib.h>

#include "../engineCore/engineWindow.h"
#include "../engineCore/gameObject.h"
#include "../engineCore/scene.h"

#include "pongBall.h"
#include "player.h"
#include "enemy.h"

int main(int argc, char const *argv[])
{
    EngineWindow w;
    EngineWindow_Init(&w, 800, 600, "Pong", FLAG_WINDOW_RESIZABLE);

    Scene s;
    Scene_Create(&s, "Scene1");

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
