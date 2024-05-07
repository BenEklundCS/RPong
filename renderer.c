//
// Created by ben on 5/6/24.
//

#include "defs.h"
#include "structs.h"

void drawPaddle(Paddle p);
void handleYBorder(Paddle *p);
void handleBallYBorder(Ball *b);

void renderer(void) {


    Paddle paddle1 = {{PADDLE_START_X, PADDLE_START_Y, PADDLE_WIDTH, PADDLE_HEIGHT},
                      BLACK};

    Paddle paddle2 = {{WINDOW_WIDTH - (PADDLE_START_X + PADDLE_WIDTH), PADDLE_START_Y, PADDLE_WIDTH, PADDLE_HEIGHT},
                      BLACK};

    Ball ball = {{(int)(WINDOW_WIDTH/2), (int)(WINDOW_HEIGHT/2), BALL_RADIUS, BALL_RADIUS},
                 WHITE,
                 {BALL_SPEED, 15}};


    bool pause = false;
    bool moving_right = true;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        if (IsKeyPressed(KEY_SPACE)) {
            TraceLog(LOG_INFO, "Game paused.");
            pause = !pause;
        }

        if (!pause)
        {
            ball.rect.x += ball.velocity.x;
            ball.rect.y += ball.velocity.y;

            handleBallYBorder(&ball);

            // Check walls collision for bouncing
            if (CheckCollisionRecs(ball.rect, paddle1.rect) && !moving_right) {
                TraceLog(LOG_INFO, "Collided with paddle1.");
                moving_right = true;
                ball.velocity.x *= -1.0f;
            }
            if (CheckCollisionRecs(ball.rect, paddle2.rect) && moving_right) {
                TraceLog(LOG_INFO, "Collided with paddle2.");
                moving_right = false;
                ball.velocity.x *= -1.0f;
            }

            // paddle1
            if (IsKeyDown(KEY_S)) {
                paddle1.rect.y += PADDLE_SPEED;
                handleYBorder(&paddle1);
            }
            if (IsKeyDown(KEY_W)) {
                paddle1.rect.y -= PADDLE_SPEED;
                handleYBorder(&paddle1);
            }

            // paddle2
            if (IsKeyDown(KEY_DOWN)) {
                paddle2.rect.y += PADDLE_SPEED;
                handleYBorder(&paddle2);
            }
            if (IsKeyDown(KEY_UP)) {
                paddle2.rect.y -= PADDLE_SPEED;
                handleYBorder(&paddle2);
            }
        }

        // Draw

        BeginDrawing();

        ClearBackground(DARKGRAY);

        drawPaddle(paddle1);
        drawPaddle(paddle2);
        DrawRectangleRec(ball.rect, ball.color);

        EndDrawing();

    }
}

void drawPaddle(Paddle p) {
    DrawRectangleRec(p.rect, p.color);
}

void handleYBorder(Paddle *p) {
    if (p->rect.y >= WINDOW_HEIGHT - p->rect.height) {
        p->rect.y = WINDOW_HEIGHT - p->rect.height;
    }
    else if (p->rect.y <= 0) {
        p->rect.y = 0;
    }
    else {
        return;
    }
}

void handleBallYBorder(Ball *b) {
    if (b->rect.y >= WINDOW_HEIGHT - b->rect.height) {
        b->rect.y = WINDOW_HEIGHT - b->rect.height;
        b->velocity.y *= -1.0f;
    }
    else if (b->rect.y <= 0) {
        b->rect.y = 0;
        b->velocity.y *= -1.0f;
    }
    else {
        return;
    }
}
