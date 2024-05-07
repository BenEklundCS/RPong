//
// Created by ben on 5/6/24.
//

#include "defs.h"
#include "structs.h"
#include "renderer.h"

// Main renderer and render loop
void renderer(void) {

    Paddle paddle1 = {{PADDLE_START_X,
                             PADDLE_START_Y,
                             PADDLE_WIDTH,
                             PADDLE_HEIGHT},
                      BLACK};

    Paddle paddle2 = {{WINDOW_WIDTH - (PADDLE_START_X + PADDLE_WIDTH),
                             PADDLE_START_Y,
                             PADDLE_WIDTH,
                             PADDLE_HEIGHT},
                      BLACK};

    Ball ball = {{(int)(WINDOW_WIDTH/2),
                        (int)(WINDOW_HEIGHT/2),
                        BALL_RADIUS,
                        BALL_RADIUS},
                 DARKPURPLE,
                 {BALL_SPEED, (int)(BALL_SPEED/2)}};


    bool pause = false;
    bool moving_right = true;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update

        if (IsKeyPressed(KEY_SPACE)) {
            TraceLog(LOG_INFO, "Game paused.");
            pause = !pause;
        }

        // If the game is not paused, then handle events
        if (!pause)
        {
            // Move the ball
            ball.rect.x += ball.speed.x * GetFrameTime();
            ball.rect.y += ball.speed.y * GetFrameTime();

            // Check for ball border collisions
            handleBallBorders(&ball);

            // Check walls collision for bouncing
            if (CheckCollisionRecs(ball.rect, paddle1.rect) && !moving_right) {
                TraceLog(LOG_INFO, "Collided with paddle1.");
                moving_right = true;
                ball.speed.x *= 1.1f;
                ball.speed.x *= -1.0f;
            }
            if (CheckCollisionRecs(ball.rect, paddle2.rect) && moving_right) {
                TraceLog(LOG_INFO, "Collided with paddle2.");
                moving_right = false;
                ball.speed.x *= 1.1f;
                ball.speed.x *= -1.0f;
            }

            // paddle1 movement
            if (IsKeyDown(KEY_S)) {
                paddle1.rect.y += PADDLE_SPEED * GetFrameTime();
                handlePaddleYBorder(&paddle1);
            }
            if (IsKeyDown(KEY_W)) {
                paddle1.rect.y -= PADDLE_SPEED * GetFrameTime();
                handlePaddleYBorder(&paddle1);
            }

            // paddle2 movement
            if (IsKeyDown(KEY_DOWN)) {
                paddle2.rect.y += PADDLE_SPEED * GetFrameTime();
                handlePaddleYBorder(&paddle2);
            }
            if (IsKeyDown(KEY_UP)) {
                paddle2.rect.y -= PADDLE_SPEED * GetFrameTime();
                handlePaddleYBorder(&paddle2);
            }
        }

        // Draw

        BeginDrawing();

        ClearBackground(DARKGRAY);

        drawPaddle(paddle1);
        drawPaddle(paddle2);
        drawBall(ball);

        EndDrawing();

    }
}

// Custom draw for paddle struct
void drawPaddle(Paddle p) {
    DrawRectangleRec(p.rect, p.color);
}

// Custom draw for ball struct
void drawBall(Ball b) {
    DrawCircle((int)b.rect.x, (int)b.rect.y, b.rect.width, b.color);
}

void handlePaddleYBorder(Paddle *p) {
    // Bottom of the screen
    if (p->rect.y >= WINDOW_HEIGHT - p->rect.height) {
        p->rect.y = WINDOW_HEIGHT - p->rect.height;
    }
    // Top of the screen
    else if (p->rect.y <= 0) {
        p->rect.y = 0;
    }
    // Didn't collide
    else {
        return;
    }
}

void handleBallBorders(Ball *b) {
    handleBallXBorder(b);
    handleBallYBorder(b);
}

void handleBallXBorder(Ball *b) {
    // Off screen
    if ((b->rect.x >= WINDOW_WIDTH + (int)(WINDOW_WIDTH/4)) || (b->rect.x <= 0 - (int)(WINDOW_WIDTH/4))) {
        b->rect.x = (int)(WINDOW_WIDTH/2);
        b->rect.y = (int)(WINDOW_HEIGHT/2);
    }
    // On screen
    else {
        return;
    }
}

void handleBallYBorder(Ball *b) {
    // Bottom of the screen
    if (b->rect.y >= WINDOW_HEIGHT - b->rect.height) {
        b->rect.y = WINDOW_HEIGHT - b->rect.height;
        b->speed.y *= -1.0f;
    }
    // Top of the screen
    else if (b->rect.y <= 0) {
        b->rect.y = 0;
        b->speed.y *= -1.0f;
    }
    // Didn't collide
    else {
        return;
    }
}
