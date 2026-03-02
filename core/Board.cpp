#include <vector>
#include "Board.h"
#include "Constants.h"
#include <algorithm>

Color board[gridRows][gridCols] = {BLANK};
int score = 0;
bool gameOver = false;

// for line clearing animation
bool isClearing = false;
float clearTimer = 0.0f;
const float clearDuration = 1.f; // 400ms blink time
std::vector<int> rowsToClear;

void DrawBoard()
{
    for (int r = 0; r < gridRows; r++)
    {
        for (int c = 0; c < gridCols; c++)
        {
            bool hideRow = false;

            if (isClearing)
            {
                for (int row : rowsToClear)
                {
                    if (row == r)
                    {
                        // Blink effect
                        if (((int)(clearTimer * 10)) % 2 == 0)
                            hideRow = true;
                    }
                }
            }

            if (!hideRow)
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

std::vector<int> GetFullRows()
{
    std::vector<int> fullRows;

    for (int r = 0; r < gridRows; r++)
    {
        if (IsRowFull(r))
            fullRows.push_back(r);
    }

    return fullRows;
}

void RemoveRows(const std::vector<int> &rows)
{
    for (int row : rows)
    {
        RemoveRow(row);
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