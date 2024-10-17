#include "ball.h"

void InitBall(Ball *ball, void *game)
{
    Location dfL = {GetScreenWidth() / 2, GetScreenHeight() / 2};
    InitBallEx(ball, game, dfL.x, dfL.y);
}

void InitBallEx(Ball *ball, void *game, int initX, int initY)
{
    if (!game)
        return;
    ball->obj.name = "Ball";
    ball->obj.location.x = initX;
    ball->obj.location.y = initY;
    ball->obj.ObjectRender = RenderBall;
    ball->obj.ObjectStart = StartBall;
    ball->obj.isVisible = 1;
    ball->obj.parentGame = game;
    GameAddGameObject((Game *)game, &ball->obj);
}

void RenderBall(GameObject *obj)
{
    if (obj->isVisible)
    {
        Ball *b = GAME_OBJECT_AS(Ball *, obj);

        if (isnan(b->velocityX) || isnan(b->velocityY))
        {
            printf("Error: Invalid velocity values\n");
            return;
        }

        printf("Velocity: (%f, %f), Speed: %f\n", b->velocityX, b->velocityY, b->speed);

        // Move the ball according to its velocity and speed
        obj->location.x += b->velocityX * b->speed;
        obj->location.y += b->velocityY * b->speed;

        printf("Ball position updated to (%d, %d)\n", obj->location.x, obj->location.y);

        // Check collision with player
        if (CheckBallPlayerCollision(b, b->player))
        {
            printf("Collision detected with player!\n");
            b->score++;
            b->speed = BALL_SPEED + b->score / 1.8f;

            // Reflect ball velocity upon collision with player
            float playerCenterX = b->player->obj.location.x + PLAYER_WIDTH / 2;
            float playerCenterY = b->player->obj.location.y + PLAYER_HEIGHT / 2;

            // Calculate the angle of incidence based on the ball's position relative to the player
            float dx = obj->location.x - playerCenterX;
            float dy = obj->location.y - playerCenterY;
            float angle = atan2(dy, dx);

            // Adjust velocity based on the angle of collision
            float speed = sqrt(b->velocityX * b->velocityX + b->velocityY * b->velocityY);
            b->velocityX = cos(angle) * speed;
            b->velocityY = sin(angle) * speed;

            // Optional: Adjust position to avoid the ball 'sticking' to the player
            if (b->obj.location.x < b->player->obj.location.x + PLAYER_WIDTH / 2)
            {
                b->obj.location.x = b->player->obj.location.x - BALL_SIZE / 2;
            }
            else
            {
                b->obj.location.x = b->player->obj.location.x + PLAYER_WIDTH + BALL_SIZE / 2;
            }
        }

        // Left bound collision
        if (obj->location.x < 5)
        {
            obj->location.x = 0;          // Reset position to the left bound
            b->velocityX = -b->velocityX; // Reverse velocity on X-axis
            ResetBall(obj);               // Reset ball when it hits the left bound
        }

        // Right bound collision
        if (obj->location.x + BALL_SIZE > GetScreenWidth())
        {
            obj->location.x = GetScreenWidth() - BALL_SIZE; // Reset position to the right bound
            b->velocityX = -b->velocityX;                   // Reverse velocity on X-axis
        }

        // Top bound collision
        if (obj->location.y < 0)
        {
            obj->location.y = 0;
            b->velocityY = -b->velocityY; // Reflect ball off the top bound
        }

        // Bottom bound collision
        if (obj->location.y + BALL_SIZE > GetScreenHeight())
        {
            obj->location.y = GetScreenHeight() - BALL_SIZE;
            b->velocityY = -b->velocityY; // Reflect ball off the bottom bound
        }

        // Draw the ball at the updated position
        DrawCircle(obj->location.x, obj->location.y, BALL_SIZE, WHITE);
    }
}

void StartBall(GameObject *obj)
{
    Ball *b = GAME_OBJECT_AS(Ball *, obj);
    VALID_PTR(b);
    printf("Ball started!\n");

    b->score = 0;
    b->initLaunchDir = rand() % 360;
    printf("Random Launch Direction: %d degrees\n", b->initLaunchDir);

    float radians = b->initLaunchDir * (PI / 180.0f);
    b->velocityX = cos(radians);
    b->velocityY = sin(radians);

    printf("Initial velocity: (%f, %f)\n", b->velocityX, b->velocityY);

    float length = sqrt((b->velocityX * b->velocityX) + (b->velocityY * b->velocityY));
    if (length > 0)
    {
        b->velocityX /= length;
        b->velocityY /= length;
    }
    else
    {
        printf("Error: Velocity length is 0, something went wrong with the normalization.\n");
        return;
    }

    b->speed = BALL_SPEED;

    b->obj.location.x = GetScreenWidth() / 2;
    b->obj.location.y = GetScreenHeight() / 2;

    printf("Ball launched at %d degrees with velocity (%f, %f)\n",
           b->initLaunchDir, b->velocityX, b->velocityY);

    // Find the Player and assign it to the ball
    Game *g = (Game *)obj->parentGame;
    GameObject *playerObj = NULL;
    if (FindGameObject(g, &playerObj, "Player"))
    {
        b->player = (Player *)playerObj;
        printf("Player found and assigned to Ball!\n");
    }
    else
    {
        printf("Error: Player not found, ball won't have a player reference.\n");
    }
}

void ResetBall(GameObject *obj)
{
    Ball *b = GAME_OBJECT_AS(Ball *, obj);
    VALID_PTR(b);

    b->score = 0;
    b->obj.location.x = GetScreenWidth() / 2;
    b->obj.location.y = GetScreenHeight() / 2;

    b->initLaunchDir = rand() % 360;
    printf("Ball reset with random launch direction: %d degrees\n", b->initLaunchDir);

    float radians = b->initLaunchDir * (PI / 180.0f);
    b->velocityX = cos(radians);
    b->velocityY = sin(radians);

    float length = sqrt((b->velocityX * b->velocityX) + (b->velocityY * b->velocityY));
    if (length > 0)
    {
        b->velocityX /= length;
        b->velocityY /= length;
    }
    else
    {
        printf("Error: Velocity length is 0 during ball reset.\n");
        return;
    }

    b->speed = BALL_SPEED;
    printf("Ball reset with new velocity (%f, %f)\n", b->velocityX, b->velocityY);
}

int CheckBallPlayerCollision(Ball *ball, Player *player)
{
    // Get ball's position and radius
    int ballX = ball->obj.location.x;
    int ballY = ball->obj.location.y;
    int ballRadius = BALL_SIZE / 2;

    // Get player's position and dimensions
    int playerX = player->obj.location.x;
    int playerY = player->obj.location.y;
    int playerWidth = PLAYER_WIDTH;
    int playerHeight = PLAYER_HEIGHT;

    // Find the closest point on the player rectangle to the ball center
    int closestX = ballX;
    int closestY = ballY;

    if (ballX < playerX)
        closestX = playerX; // Ball is to the left of the player
    else if (ballX > playerX + playerWidth)
        closestX = playerX + playerWidth; // Ball is to the right of the player

    if (ballY < playerY)
        closestY = playerY; // Ball is above the player
    else if (ballY > playerY + playerHeight)
        closestY = playerY + playerHeight; // Ball is below the player

    // Calculate the distance between the ball's center and the closest point on the player rectangle
    int dx = ballX - closestX;
    int dy = ballY - closestY;
    float distanceSquared = dx * dx + dy * dy; // Use squared distance to avoid floating-point operations

    // Check if the distance is less than or equal to the ball's radius squared
    return distanceSquared <= (ballRadius * ballRadius);
}
