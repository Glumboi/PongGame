#ifndef PLAYER_SHARED_H
#define PLAYER_SHARED_H

#include <raylib.h>
#include <stdio.h>

#include "../engineCore/gameObject.h"

#define PLAYER_HEIGHT 200
#define PLAYER_WIDTH 25
#define SCORE_OFFSET_TOP 25
#define PLAYER_SPEED 800

typedef struct player {
  GameObject obj;
  int score;
  float moveSpeed;
} Player;

inline void Player_HandleMovement(GameObject *obj, KeyboardKey up,
                                  KeyboardKey down) {
  float movement = ((Player *)obj)->moveSpeed * GetFrameTime();
  if (IsKeyDown(up))
    obj->location.y -= movement; // Move up
  if (IsKeyDown(down))
    obj->location.y += movement; // Move down

  if (obj->location.y < 0)
    obj->location.y = 0;
  if (obj->location.y > GetScreenHeight() - PLAYER_HEIGHT)
    obj->location.y = GetScreenHeight() - PLAYER_HEIGHT;
}

inline void DrawRoundedRectangle(int x, int y, int width, int height,
                                 int radius, Color color) {
  // Draw the center of the rectangle (excluding corners)
  DrawRectangle(x + radius, y, width - 2 * radius, height, color); // Top side
  DrawRectangle(x + radius, y + height - radius, width - 2 * radius, radius,
                color); // Bottom side
  DrawRectangle(x, y + radius, radius, height - 2 * radius, color); // Left side
  DrawRectangle(x + width - radius, y + radius, radius, height - 2 * radius,
                color); // Right side

  // Draw the four corners
  DrawCircle(x + radius, y + radius, radius, color);         // Top-left corner
  DrawCircle(x + width - radius, y + radius, radius, color); // Top-right corner
  DrawCircle(x + radius, y + height - radius, radius,
             color); // Bottom-left corner
  DrawCircle(x + width - radius, y + height - radius, radius,
             color); // Bottom-right corner
}

void Player_OnStart(GameObject *obj);

#endif
