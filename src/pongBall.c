#include "pongBall.h"

void PongBall_Init(PongBall *ball) {
  if (!ball)
    return;
  ball->obj = GameObject_NewName("Ball");
  ball->obj.OnUpdate = PongBall_OnUpdate;
  ball->obj.OnStart = PongBall_OnStart;
  ball->hasAnyPlayerPressedAButton = 0;
  ball->velocityX = 0;
  ball->velocityY = 0;
  ball->moveSpeed = 0;
  ball->player = NULL;
}

void PongBall_OnStart(GameObject *obj) {
  if (!obj)
    return;

  printf("Ball started!\n");

  PongBall *ball = (PongBall *)obj;

  Scene_FindGameObject(obj->parentScene, &ball->player, "Player1", 1);
  Scene_FindGameObject(obj->parentScene, &ball->player2, "Player2", 1);

  ball->initLaunchDir = rand() % 180;

  float radians = ball->initLaunchDir * (M_PI / 180.0f);
  ball->velocityX = cos(radians);
  ball->velocityY = sin(radians);

  printf("Initial velocity: (%f, %f)\n", ball->velocityX, ball->velocityY);

  float length = sqrt((ball->velocityX * ball->velocityX) +
                      (ball->velocityY * ball->velocityY));
  if (length > 0) {
    ball->velocityX /= length;
    ball->velocityY /= length;
  } else {
    printf("Error: Velocity length is 0, something went wrong with the "
           "normalization.\n");
    return;
  }

  ball->moveSpeed = BALL_SPEED;
  ball->obj.location.x = GetScreenWidth() / 2;
  ball->obj.location.y = GetScreenHeight() / 2;

  printf("Ball launched at %d degrees with velocity (%f, %f)\n",
         ball->initLaunchDir, ball->velocityX, ball->velocityY);
}

void PongBall_OnUpdate(GameObject *obj) {
  if (!obj)
    return;

  PongBall *ball = (PongBall *)obj;
  if (IsKeyPressed(GetKeyPressed())) {
    ball->hasAnyPlayerPressedAButton = 1;
  }

  if (obj->isVisible) {
    if (!ball->hasAnyPlayerPressedAButton) {
      DrawText("Any player press a button to start", GetScreenWidth() / 2 - 310,
               GetScreenHeight() / 2 + 20, 35, WHITE);
      return;
    }
    if (isnan(ball->velocityX) || isnan(ball->velocityY)) {
      printf("Error: Invalid velocity values\n");
      return;
    }

    // Move the ball
    obj->location.x += ball->velocityX * ball->moveSpeed * GetScreenWidth() *
                       GetFrameTime() / WINDOW_WIDTH_SPEED_MULTIPLIER;
    obj->location.y += ball->velocityY * ball->moveSpeed * GetScreenWidth() *
                       GetFrameTime() / WINDOW_WIDTH_SPEED_MULTIPLIER;

    // Check for collisions
    PongBall_CollisionChecks(obj, ball->player);
    PongBall_CollisionChecks(obj, ball->player2);

    // Check for screen bounds collisions
    if (obj->location.x < 5) {
      ball->velocityX = -ball->velocityX;
      PongBall_Reset(obj);
    } else if (obj->location.x + BALL_SIZE > GetScreenWidth()) {
      ball->velocityX = -ball->velocityX;
      PongBall_Reset(obj);
    }

    if (obj->location.y < 0) {
      ball->velocityY = -ball->velocityY;
    } else if (obj->location.y + BALL_SIZE > GetScreenHeight()) {
      ball->velocityY = -ball->velocityY;
    }

    // Draw the ball at the updated position
    DrawCircle(obj->location.x, obj->location.y, BALL_SIZE, WHITE);
  }
}

void PongBall_Reset(GameObject *obj) {
  PongBall *ball = (PongBall *)obj;
  ball->obj.location.x = GetScreenWidth() / 2;
  ball->obj.location.y = GetScreenHeight() / 2;

  ball->hasAnyPlayerPressedAButton = 0;
  ball->initLaunchDir = rand() % 180;
  printf("Ball reset with random launch direction: %d degrees\n",
         ball->initLaunchDir);

  float radians = ball->initLaunchDir * (PI / 180.0f);
  ball->velocityX = cos(radians);
  ball->velocityY = sin(radians);

  float length = sqrt((ball->velocityX * ball->velocityX) +
                      (ball->velocityY * ball->velocityY));
  if (length > 0) {
    ball->velocityX /= length;
    ball->velocityY /= length;
  } else {
    printf("Error: Velocity length is 0 during ball reset.\n");
    return;
  }

  ball->moveSpeed = BALL_SPEED;
  printf("Ball reset with new velocity (%f, %f)\n", ball->velocityX,
         ball->velocityY);

  if (ball->lastHittingPlayer)
    ((Player *)ball->lastHittingPlayer)->score++;
}

void PongBall_CollisionChecks(GameObject *ballObj, GameObject *targetObject) {
  // Code made with help of AI for now

  if (!ballObj || !targetObject)
    return;

  PongBall *ball = (PongBall *)ballObj;
  Player *player = (Player *)targetObject;

  // Get the ball's position and radius
  float ballX = ballObj->location.x;
  float ballY = ballObj->location.y;
  float ballRadius = BALL_SIZE / 2;

  // Get the player's position and size (assuming the player object is a
  // rectangle)
  float playerX = player->obj.location.x;
  float playerY = player->obj.location.y;
  float playerWidth = PLAYER_WIDTH;
  float playerHeight = PLAYER_HEIGHT;

  // AABB collision check
  bool collisionX = ballX + ballRadius > playerX &&
                    ballX - ballRadius < playerX + playerWidth;
  bool collisionY = ballY + ballRadius > playerY &&
                    ballY - ballRadius < playerY + playerHeight;

  if (collisionX && collisionY) {
    // Collision detected, reverse ball direction
    ball->velocityX = -ball->velocityX;

    // Adjust ball moveSpeed or direction based on collision point
    float impactPoint = (ballY - playerY) /
                        playerHeight; // Value between 0 (top) and 1 (bottom)
    ball->velocityY = (impactPoint - 0.5f) *
                      2; // Adjust based on where the ball hits on the paddle

    // Normalize velocity to keep consistent moveSpeed
    float length = sqrt(ball->velocityX * ball->velocityX +
                        ball->velocityY * ball->velocityY);
    if (length > 0) {
      ball->velocityX /= length;
      ball->velocityY /= length;
    }

    // player->score++;
    ball->lastHittingPlayer = player;
    ball->moveSpeed += 30;

    // Move the ball outside the player's bounds based on ball's direction
    if (ball->velocityX > 0) {
      // Ball is moving to the right, place it to the right of the paddle
      ballObj->location.x = playerX + playerWidth + ballRadius;
    } else {
      // Ball is moving to the left, place it to the left of the paddle
      ballObj->location.x = playerX - ballRadius;
    }
  }
}
