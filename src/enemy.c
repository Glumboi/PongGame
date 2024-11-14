#include "enemy.h"

void Enemy_Init(Player *player2) {
  if (!player2)
    return;
  player2->obj = GameObject_NewName("Player2");
  player2->obj.OnStart = Player_OnStart;
  player2->obj.OnUpdate = Enemy_OnUpdate;
  player2->obj.location =
      (Location){GetScreenWidth() - 35, GetScreenHeight() / 2 - PLAYER_HEIGHT};
  player2->score = 0;
  player2->moveSpeed = PLAYER_SPEED;
}

void Enemy_OnUpdate(GameObject *obj) {
  Player_HandleMovement(obj, KEY_UP, KEY_DOWN);

  // Set player2 to right screen bounds
  obj->location.x = GetScreenWidth() - 35;

  Player *player = (Player *)obj;
  if (obj->isVisible) {
    DrawRoundedRectangle(obj->location.x, obj->location.y, PLAYER_WIDTH,
                         PLAYER_HEIGHT, 10, WHITE);

    DrawText(TextFormat("Score: %d", player->score),
             obj->location.x - ENEMY_SCORE_OFFSET_LEFT,
             obj->location.y - SCORE_OFFSET_TOP, 24, WHITE);
  }
}
