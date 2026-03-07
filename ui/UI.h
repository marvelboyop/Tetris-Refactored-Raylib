#pragma once
#include "../shapes/Shape.h"

void DrawUI(int score, int highScore, Shape *nextShape, bool gameOver);
void DrawNextShape(Shape *shape, int startX, int startY);