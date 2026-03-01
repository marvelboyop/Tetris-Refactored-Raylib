#pragma once
#include <raylib.h>
#include <vector>
#include "Constants.h"

extern Color board[gridRows][gridCols];
extern int score;
extern bool gameOver;

void DrawBoard();
bool IsRowFull(int row);
void RemoveRow(int row);
int ClearLines();