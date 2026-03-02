#pragma once
#include <raylib.h>
#include <vector>
#include "Constants.h"

extern Color board[gridRows][gridCols];
extern int score;
extern bool gameOver;

extern bool isClearing;
extern float clearTimer;
extern const float clearDuration;
extern std::vector<int> rowsToClear;
void RemoveRows(const std::vector<int> &rows);
std::vector<int> GetFullRows();

void DrawBoard();
bool IsRowFull(int row);
void RemoveRow(int row);
int ClearLines();