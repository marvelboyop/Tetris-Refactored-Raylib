#include "Shape.h"
//======================================= Square ==========================================
class Square : public Shape
{
public:
    Square() : Shape(2, BLUE)
    {
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
    }
};

//======================================== T Shape =================================
class TShape : public Shape
{
public:
    TShape() : Shape(3, GREEN)
    {
        matrix[0][1] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
    }
};

// ====================================== Z shape =============================

class ZShape : public Shape
{
public:
    ZShape() : Shape(3, YELLOW)
    {
        matrix[0][0] = 1;
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
    }
};

// =============================== L shape ===================================
class LShape : public Shape
{
public:
    LShape() : Shape(3, ORANGE)
    {
        matrix[0][0] = 1;
        matrix[1][0] = 1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
    }
};

// =========================== line ============================================
class line : public Shape
{
public:
    line() : Shape(4, RED)
    {
        matrix[1][0] = 1;
        matrix[1][1] = 1;
        matrix[1][2] = 1;
        matrix[1][3] = 1;
    }
};

//=========================== S Shape ====================================
class SShape : public Shape
{
public:
    SShape() : Shape(3, PINK)
    {
        matrix[0][1] = 1;
        matrix[0][2] = 1;
        matrix[1][0] = 1;
        matrix[1][1] = 1;
    }
};

//========================== J Shape ========================================
class JShape : public Shape
{
public:
    JShape() : Shape(3, GRAY)
    {
        matrix[0][1] = 1;
        matrix[1][1] = 1;
        matrix[2][0] = 1;
        matrix[2][1] = 1;
    }
};
