//
// Created by ben on 5/6/24.
//

#ifndef MYRAYLIBGAME_RENDERER_H
#define MYRAYLIBGAME_RENDERER_H

void drawPaddle(Paddle p);
void drawBall(Ball b);
void handlePaddleYBorder(Paddle *p);
void handleBallBorders(Ball *b);
void handleBallYBorder(Ball *b);
void handleBallXBorder(Ball *b);

#endif //MYRAYLIBGAME_RENDERER_H
