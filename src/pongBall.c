#include "pongBall.h"

void PongBall_Init(PongBall *ball)
{
    if (!ball)
        return;
    ball->obj = GameObject_NewName("Ball");
    ball->obj.OnUpdate = PongBall_OnUpdate;
    ball->obj.OnStart = PongBall_OnStart;

    ball->velocityX = 0;
    ball->velocityY = 0;
    ball->speed = 0;
    ball->player = NULL;
}

void PongBall_OnStart(GameObject *obj)
{
    if (!obj)
        return;

    printf("Ball started!\n");

    PongBall *ball = (PongBall *)obj;

    Scene_FindGameObject(obj->parentScene, &ball->player, "Player1", 1);
    Scene_FindGameObject(obj->parentScene, &ball->enemy, "Player2", 1);

    ball->initLaunchDir = rand() % 180;

    float radians = ball->initLaunchDir * (M_PI / 180.0f);
    ball->velocityX = cos(radians);
    ball->velocityY = sin(radians);

    printf("Initial velocity: (%f, %f)\n", ball->velocityX, ball->velocityY);

    float length = sqrt((ball->velocityX * ball->velocityX) + (ball->velocityY * ball->velocityY));
    if (length > 0)
    {
        ball->velocityX /= length;
        ball->velocityY /= length;
    }
    else
    {
        printf("Error: Velocity length is 0, something went wrong with the normalization.\n");
        return;
    }

    ball->speed = BALL_SPEED;

    ball->obj.location.x = GetScreenWidth() / 2;
    ball->obj.location.y = GetScreenHeight() / 2;

    printf("Ball launched at %d degrees with velocity (%f, %f)\n",
           ball->initLaunchDir, ball->velocityX, ball->velocityY);
}

void PongBall_OnUpdate(GameObject *obj)
{
    if (!obj)
        return;

    if (obj->isVisible)
    {
        PongBall *ball = (PongBall *)obj;
        if (isnan(ball->velocityX) || isnan(ball->velocityY))
        {
            printf("Error: Invalid velocity values\n");
            return;
        }

        // Move the ball
        obj->location.x += ball->velocityX * ball->speed * GetScreenWidth() / WINDOW_WIDTH_SPEED_MULTIPLIER;
        obj->location.y += ball->velocityY * ball->speed * GetScreenWidth() / WINDOW_WIDTH_SPEED_MULTIPLIER;

        // Check for collisions
        PongBall_CollisionChecks(obj, ball->player);
        PongBall_CollisionChecks(obj, ball->enemy);

        // Check for screen bounds collisions
        if (obj->location.x < 5)
        {
            ball->velocityX = -ball->velocityX;
            PongBall_Reset(obj);
        }
        else if (obj->location.x + BALL_SIZE > GetScreenWidth())
        {
            ball->velocityX = -ball->velocityX;
            PongBall_Reset(obj);
        }

        if (obj->location.y < 0)
        {
            ball->velocityY = -ball->velocityY;
        }
        else if (obj->location.y + BALL_SIZE > GetScreenHeight())
        {
            ball->velocityY = -ball->velocityY;
        }

        // Draw the ball at the updated position
        DrawCircle(obj->location.x, obj->location.y, BALL_SIZE, WHITE);
    }
}

void PongBall_Reset(GameObject *obj)
{
    PongBall *ball = (PongBall *)obj;

    ball->obj.location.x = GetScreenWidth() / 2;
    ball->obj.location.y = GetScreenHeight() / 2;

    ball->initLaunchDir = rand() % 180;
    printf("Ball reset with random launch direction: %d degrees\n", ball->initLaunchDir);

    float radians = ball->initLaunchDir * (PI / 180.0f);
    ball->velocityX = cos(radians);
    ball->velocityY = sin(radians);

    float length = sqrt((ball->velocityX * ball->velocityX) + (ball->velocityY * ball->velocityY));
    if (length > 0)
    {
        ball->velocityX /= length;
        ball->velocityY /= length;
    }
    else
    {
        printf("Error: Velocity length is 0 during ball reset.\n");
        return;
    }

    ball->speed = BALL_SPEED;
    printf("Ball reset with new velocity (%f, %f)\n", ball->velocityX, ball->velocityY);
}

void PongBall_CollisionChecks(GameObject *ballObj, GameObject *targetObject)
{
    // Code made with help of AI for now

    if (!ballObj || !targetObject)
        return;

    PongBall *ball = (PongBall *)ballObj;
    Player *player = (Player *)targetObject;

    // Get the ball's position and radius
    float ballX = ballObj->location.x;
    float ballY = ballObj->location.y;
    float ballRadius = BALL_SIZE / 2;

    // Get the player's position and size (assuming the player object is a rectangle)
    float playerX = player->obj.location.x;
    float playerY = player->obj.location.y;
    float playerWidth = PLAYER_WIDTH;
    float playerHeight = PLAYER_HEIGHT;

    // AABB collision check
    bool collisionX = ballX + ballRadius > playerX && ballX - ballRadius < playerX + playerWidth;
    bool collisionY = ballY + ballRadius > playerY && ballY - ballRadius < playerY + playerHeight;

    if (collisionX && collisionY)
    {
        // Collision detected, reverse ball direction
        ball->velocityX = -ball->velocityX;

        // Adjust ball speed or direction based on collision point
        // For example, if the ball hits near the top or bottom of the paddle,
        // we can add a small angle variation to the Y velocity for a more dynamic game.
        float impactPoint = (ballY - playerY) / playerHeight; // Value between 0 (top) and 1 (bottom)
        ball->velocityY = (impactPoint - 0.5f) * 2;           // Adjust based on where the ball hits on the paddle

        // Normalize velocity to keep consistent speed
        float length = sqrt(ball->velocityX * ball->velocityX + ball->velocityY * ball->velocityY);
        if (length > 0)
        {
            ball->velocityX /= length;
            ball->velocityY /= length;
        }

        player->score++;
        ball->speed += 0.1; // Optionally increase speed after each hit
    }

    // Ball goes out of bounds on the left side (player misses it)
    if (ballX < 0)
    {
        printf("Player missed the ball! Resetting...\n");
        PongBall_Reset(ballObj);
    }
}
