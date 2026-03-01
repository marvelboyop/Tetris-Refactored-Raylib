#pragma once
#include <raylib.h>
#include "../core/Board.h"
#include "../core/Constants.h"

class Shape
{
public:
    int matrix[4][4];
    int size;
    int posX, posY;
    bool isLocked;
    Color color;

    float fallTimer = 0.0f;
    float fallDelay = 0.5f; // for storing the current fall delay
    float normalFallDelay = 0.5f;
    float softDropDelay = 0.05f;

    Shape(int s, Color c);
    virtual ~Shape() {}

    void Update();
    void Draw();

    void LockToBoard();

protected:
    bool CanMoveDown();
    bool CanMoveLeft();
    bool CanMoveRight();
    void Rotate();
    bool CanRotate(int temp[4][4]);
};

bool CanSpawn(Shape *shape);
void DrawNextShape(Shape *shape, int startX, int startY);