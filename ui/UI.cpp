#include "UI.h"
#include "../core/Constants.h"
#include "../core/Board.h"
#include <raylib.h>

void DrawUI(int score, Shape *nextShape, bool gameOver)
{
     // Grid by drawing lines
        for (int row = 0; row < gridRows; row++)
        {
            for (int col = 0; col < gridCols; col++)
            {
                DrawRectangleLines(
                    col * cellSize,
                    row * cellSize,
                    cellSize,
                    cellSize,
                    WHITE);
            }
        }

        int PrintInfoX = gridCols * cellSize + 120;
        DrawText("SCORE", PrintInfoX, 60, 40, WHITE);
        DrawText(TextFormat("%d", score), PrintInfoX, 120, 40, YELLOW);

        DrawText("NEXT", PrintInfoX, 320, 40, WHITE);
        DrawNextShape(nextShape, PrintInfoX - 20, 400);
        // Draw grid lines ONLY around preview area
        for (int r = 0; r <= nextShape->size; r++)
        {
            DrawLine(
                PrintInfoX - 20,
                400 + r * cellSize,
                PrintInfoX - 20 + nextShape->size * cellSize,
                400 + r * cellSize,
                WHITE);
        }

        for (int c = 0; c <= nextShape->size; c++)
        {
            DrawLine(
                PrintInfoX - 20 + c * cellSize,
                400,
                PrintInfoX - 20 + c * cellSize,
                400 + nextShape->size * cellSize,
                WHITE);
        }
        if (gameOver)
        {
            DrawText(
                "GAME OVER",
                gridCols * cellSize / 2 - 140 - 45,
                screen_height / 2 - 20,
                60,
                GOLD);
        }
        DrawText("marvelboyop", 620, 709, 28, GOLD);
        DrawText("&", 695, 744, 28, GOLD);
        DrawText("Dwip", 675, 777, 28, GOLD);
}