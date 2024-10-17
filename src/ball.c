#include "ball.h"

void InitBall(Ball *ball, Game *game)
{
    Location dfL = {GetScreenWidth() / 2, GetScreenHeight() / 2};
    InitBallEx(ball, game, dfL.x, dfL.y);
}

void InitBallEx(Ball *ball, Game *game, int initX, int initY)
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
    GameAddGameObject(game, &ball->obj);
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

        // Move the ball
        obj->location.x += b->velocityX * b->speed * GetScreenWidth() / WINDOW_WIDTH_SPEED_MULTIPLIER;
        obj->location.y += b->velocityY * b->speed * GetScreenWidth() / WINDOW_WIDTH_SPEED_MULTIPLIER;

        // Check for collisions
        CheckBallPlayerCollision(b, b->enemy);
        CheckBallPlayerCollision(b, b->player);

        // Check for screen bounds collisions
        if (obj->location.x < 5)
        {
            b->velocityX = -b->velocityX;
            ResetBall(obj);
        }
        else if (obj->location.x + BALL_SIZE > GetScreenWidth())
        {
            b->velocityX = -b->velocityX;
            ResetBall(obj);
        }

        if (obj->location.y < 0)
        {
            b->velocityY = -b->velocityY;
        }
        else if (obj->location.y + BALL_SIZE > GetScreenHeight())
        {
            b->velocityY = -b->velocityY;
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

    b->initLaunchDir = rand() % 180;
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

    Game *g = (Game *)obj->parentGame;

    if (FindGameObject(g, &b->player, "Player"))
        printf("Player found and assigned to Ball!\n");

    if (FindGameObject(g, &b->enemy, "Enemy"))
        printf("Enemy found and assigned to Ball!\n");
}

void ResetBall(GameObject *obj)
{
    Ball *b = GAME_OBJECT_AS(Ball *, obj);
    VALID_PTR(b);

    b->obj.location.x = GetScreenWidth() / 2;
    b->obj.location.y = GetScreenHeight() / 2;

    b->initLaunchDir = rand() % 180;
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

void CheckBallPlayerCollision(Ball *ball, BallAware *scoreObject)
{
    // Get ball's position and radius
    int ballX = ball->obj.location.x;
    int ballY = ball->obj.location.y;
    int ballRadius = BALL_SIZE / 2;

    // Get player's position and dimensions
    int playerX = scoreObject->obj.location.x;
    int playerY = scoreObject->obj.location.y;
    int playerWidth = PLAYER_WIDTH;
    int playerHeight = PLAYER_HEIGHT;

    // Find the closest point on the player rectangle to the ball center
    int closestX = (ballX < playerX) ? playerX : (ballX > playerX + playerWidth) ? playerX + playerWidth
                                                                                 : ballX;
    int closestY = (ballY < playerY) ? playerY : (ballY > playerY + playerHeight) ? playerY + playerHeight
                                                                                  : ballY;

    // Calculate the distance between the ball's center and the closest point
    int dx = ballX - closestX;
    int dy = ballY - closestY;
    int distanceSquared = dx * dx + dy * dy;

    // If the distance is less than the ball's radius, a collision has occurred
    if (distanceSquared < ballRadius * ballRadius)
    {
        // Reflect ball velocity upon collision with player
        float playerCenterX = playerX + playerWidth / 2;
        float playerCenterY = playerY + playerHeight / 2;

        // Calculate angle of reflection
        float dx = ballX - playerCenterX;
        float dy = ballY - playerCenterY;
        float angle = atan2(dy, dx);

        // Adjust velocity based on the angle
        float speed = sqrt(ball->velocityX * ball->velocityX + ball->velocityY * ball->velocityY);
        ball->velocityX = cos(angle) * speed;
        ball->velocityY = sin(angle) * speed;

        if (ball->obj.location.x < playerX + playerWidth / 2)
        {
            ball->obj.location.x = playerX - BALL_SIZE / 2;
        }
        else
        {
            ball->obj.location.x = playerX + playerWidth + BALL_SIZE / 2;
        }

        // Increment score and adjust speed
        scoreObject->score++;
        ball->speed = BALL_SPEED + scoreObject->score / 1.8f;

        printf("Collision detected with player!\n");
    }
}