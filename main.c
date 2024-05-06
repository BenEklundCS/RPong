/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "init.c"
#include "structs.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

// private defs
void drawPaddle(Paddle p);
void handleYBorder(Paddle *p);

int main(void)
{

    init();

    Rectangle paddle1_rect = {PADDLE_START_X,PADDLE_START_Y,PADDLE_WIDTH,PADDLE_HEIGHT};
    Paddle paddle1 = {paddle1_rect, BLACK};

    Rectangle paddle2_rect = {WINDOW_WIDTH - (PADDLE_START_X + PADDLE_WIDTH),
                              PADDLE_START_Y,PADDLE_WIDTH,PADDLE_HEIGHT};
    Paddle paddle2 = {paddle2_rect, BLACK};

    Rectangle ball_rect = {(int)(WINDOW_WIDTH/2), (int)(WINDOW_HEIGHT/2), 50, 50};
    Ball ball = {ball_rect, WHITE};



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // paddle1
        if (IsKeyDown(KEY_S)) {
            paddle1.rect.y += PLAYER_SPEED;
            handleYBorder(&paddle1);
        }
        if (IsKeyDown(KEY_W)) {
            paddle1.rect.y -= PLAYER_SPEED;
            handleYBorder(&paddle1);
        }


        // paddle2

        if (IsKeyDown(KEY_DOWN)) {
            paddle2.rect.y += PLAYER_SPEED;
            handleYBorder(&paddle2);
        }
        if (IsKeyDown(KEY_UP)) {
            paddle2.rect.y -= PLAYER_SPEED;
            handleYBorder(&paddle2);
        }

        // Draw

        BeginDrawing();

        ClearBackground(DARKGRAY);

        drawPaddle(paddle1);
        drawPaddle(paddle2);
        DrawRectangleRec(ball.rect, ball.color);

        EndDrawing();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    exit(EXIT_SUCCESS);
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


