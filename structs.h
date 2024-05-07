//
// Created by ben on 5/6/24.
//

#include <raylib.h>

#ifndef MYRAYLIBGAME_STRUCTS_H
#define MYRAYLIBGAME_STRUCTS_H

typedef struct {
    Rectangle rect;
    Color color;
} Paddle;

typedef struct {
    Rectangle rect;
    Color color;
    Vector2 speed;
} Ball;

#endif //MYRAYLIBGAME_STRUCTS_H
