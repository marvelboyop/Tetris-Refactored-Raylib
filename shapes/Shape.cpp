#include "Shape.h"
#include "../core/Board.h"
#include "../core/Board.h"

Shape::Shape(int s, Color c) : size(s), color(c)
{
    posX = gridCols / 2 - 1;
    posY = 0;

    // Clear matrix
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j] = 0;
}

// ---------- DRAW ----------
void Shape::Draw()
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (matrix[r][c] == 1)
            {
                DrawRectangle(
                    (posX + c) * cellSize,
                    (posY + r) * cellSize,
                    cellSize,
                    cellSize,
                    color);
            }
        }
    }
}

// ---------- UPDATE ----------
void Shape::Update()
{
    if (isLocked)
        return;

    // Soft Drop
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        fallDelay = softDropDelay;
    else
        fallDelay = normalFallDelay;

    // Gravity
    fallTimer += GetFrameTime();
    if (fallTimer >= fallDelay)
    {
        if (CanMoveDown())
        {
            posY++;
        }
        else
        {
            LockToBoard();

            int lines = ClearLines();
            score += lines * lines * 100;

            isLocked = true;
        }

        fallTimer = 0.0f;
    }

    // Horizontal movement
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
    {
        if (CanMoveLeft())
            posX--;
    }

    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
    {
        if (CanMoveRight())
            posX++;
    }

    // rotation
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
    {
        Rotate();
    }
}

//============================== Can Move Right?? ==============================
bool Shape::CanMoveRight()
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (matrix[r][c] == 1)
            {
                int nextCol = posX + c + 1;

                // Hit right wall
                if (nextCol >= gridCols)
                    return false;

                // Hit another block
                if (board[posY + r][nextCol].a != 0)
                    return false;
            }
        }
    }
    return true;
}

// ============================== Can Move Left ?? ===============================
bool Shape::CanMoveLeft()
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (matrix[r][c] == 1)
            {
                int nextCol = posX + c - 1;

                // Hit left wall
                if (nextCol < 0)
                    return false;

                // Hit another block
                if (board[posY + r][nextCol].a != 0)
                    return false;
            }
        }
    }
    return true;
}
// ========================= Can Rotate?? ======================
bool Shape::CanRotate(int temp[4][4])
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (temp[r][c] == 1)
            {
                int boardX = posX + c;
                int boardY = posY + r;

                // Out of bounds
                if (boardX < 0 || boardX >= gridCols ||
                    boardY < 0 || boardY >= gridRows)
                    return false;

                // Hit locked block
                if (board[boardY][boardX].a != 0)
                    return false;
            }
        }
    }
    return true;
}

//======================= rotate =============================
void Shape::Rotate()
{
    int temp[4][4] = {0};

    // Rotate clockwise
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            temp[c][size - 1 - r] = matrix[r][c];
        }
    }
    // Check if rotation is valid
    if (CanRotate(temp))
    {
        // Apply rotation
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                matrix[r][c] = temp[r][c];
    }
}

// Draw the shape to board when it touches the ground
void Shape::LockToBoard()
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (matrix[r][c] == 1)
            {
                board[posY + r][posX + c] = color;
            }
        }
    }
}

//======================== Can Move Down ??? =============================
bool Shape::CanMoveDown()
{
    for (int r = 0; r < size; r++)
    {
        for (int c = 0; c < size; c++)
        {
            if (matrix[r][c] == 1)
            {
                int nextRow = posY + r + 1;

                // Hit bottom of grid
                if (nextRow >= gridRows)
                    return false;

                // (Later) hit another block
                if (board[nextRow][posX + c].a != 0)
                    return false;
            }
        }
    }
    return true;
}

//============================ CanSpawn ===============================
bool CanSpawn(Shape *shape)
{
    for (int r = 0; r < shape->size; r++)
    {
        for (int c = 0; c < shape->size; c++)
        {
            if (shape->matrix[r][c] == 1)
            {
                int boardX = shape->posX + c;
                int boardY = shape->posY + r;

                // Outside board (should not happen, but safe)
                if (boardY < 0 || boardY >= gridRows ||
                    boardX < 0 || boardX >= gridCols)
                    return false;

                // Collision with existing block
                if (board[boardY][boardX].a != 0)
                    return false;
            }
        }
    }
    return true;
}

// ============================== Draw Next Shape ==================================
void DrawNextShape(Shape *shape, int startX, int startY)
{
    for (int r = 0; r < shape->size; r++)
    {
        for (int c = 0; c < shape->size; c++)
        {
            if (shape->matrix[r][c] == 1)
            {
                DrawRectangle(
                    startX + c * cellSize,
                    startY + r * cellSize,
                    cellSize,
                    cellSize,
                    shape->color);
            }
        }
    }
}
