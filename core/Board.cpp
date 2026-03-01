#include <vector>
#include "Board.h"
#include "Constants.h"
#include <algorithm>

Color board[gridRows][gridCols] = {BLANK};
int score = 0;
bool gameOver = false;

void DrawBoard()
{
    for (int r = 0; r < gridRows; r++)
    {
        for (int c = 0; c < gridCols; c++)
        {
            DrawRectangle(
                c * cellSize,
                r * cellSize,
                cellSize,
                cellSize,
                board[r][c]);
        }
    }
}

// ======================================= isRowFull ?? ===========================
bool IsRowFull(int row)
{
    for (int c = 0; c < gridCols; c++)
    {
        if (board[row][c].a == 0)
            return false;
    }
    return true;
}

// ======================================= Remove Row ===========================
void RemoveRow(int row)
{
    for (int r = row; r > 0; r--)
    {
        for (int c = 0; c < gridCols; c++)
        {
            board[r][c] = board[r - 1][c];
        }
    }

    // Clear the top row
    for (int c = 0; c < gridCols; c++)
    {
        board[0][c] = BLANK;
    }
}

int ClearLines()
{
    int linesClearedThisTurn = 0;

    for (int r = gridRows - 1; r >= 0; r--)
    {
        if (IsRowFull(r))
        {
            RemoveRow(r);
            linesClearedThisTurn++;
            r++; // recheck same row
        }
    }

    return linesClearedThisTurn;
}