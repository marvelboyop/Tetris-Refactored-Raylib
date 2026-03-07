#include <iostream>
#include <raylib.h>
#include "core/Constants.h"
#include "core/Board.h"
#include "shapes/Shape.h"
#include "shapes/Tetrominoes.h"
#include "systems/Bag.h"
#include "ui/UI.h"
#include "systems/HighScore.h"
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
    InitWindow(screen_width, screen_height, "Tetris made by marvelboyop & Dwip");
    SetTargetFPS(60);

    int highScore = LoadHighScore();

    Shape *currentShape = SpawnShape();
    Shape *nextShape = SpawnShape();

    while (!WindowShouldClose())
    {
        // Update
        if (!gameOver)
        {

            if (isClearing)
            {
                clearTimer += GetFrameTime();

                if (clearTimer >= clearDuration)
                {
                    RemoveRows(rowsToClear);

                    int lines = rowsToClear.size();
                    score += lines * lines * 100;

                    rowsToClear.clear();
                    isClearing = false;

                    currentShape->isLocked = true;
                }

                // Skip normal gameplay while blinking
            }
            else
            {
                currentShape->Update();
            }

            if (currentShape->isLocked)
            {
                delete currentShape;
                currentShape = nextShape;
                nextShape = SpawnShape();

                if (!CanSpawn(currentShape))
                    gameOver = true;
            }
        }

        // update highscore live
        if (score > highScore)
        {
            highScore = score;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawBoard();
        // to prevent drawing the currentShape when the animation is happening
        if (!isClearing)
        {
            currentShape->Draw();
        }
        DrawUI(score, highScore, nextShape, gameOver);
        EndDrawing();
    }

    delete currentShape;
    delete nextShape;

    SaveHighScore(highScore);

    CloseWindow();
    return 0;
}