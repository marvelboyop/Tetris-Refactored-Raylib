#include <iostream>
#include <raylib.h>
#include "core/Constants.h"
#include "core/Board.h"
#include "shapes/Shape.h"
#include "shapes/Tetrominoes.h"
#include "systems/Bag.h"
#include "ui/UI.h"
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
    InitWindow(screen_width, screen_height, "Tetris made by marvelboyop & Dwip");
    SetTargetFPS(60);

    Shape *currentShape = SpawnShape();
    Shape *nextShape = SpawnShape();

    while (!WindowShouldClose())
    {
        // Update
        if (!gameOver)
        {
            currentShape->Update();

            if (currentShape->isLocked)
            {
                delete currentShape;
                currentShape = nextShape;
                nextShape = SpawnShape();

                if (!CanSpawn(currentShape))
                    gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawBoard();
        currentShape->Draw();
        DrawUI(score, nextShape, gameOver);
        EndDrawing();
    }

    delete currentShape;
    delete nextShape;
    CloseWindow();
    return 0;
}