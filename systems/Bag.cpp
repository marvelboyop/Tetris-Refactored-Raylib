#include "Bag.h"
#include <algorithm>
#include "../shapes/Tetrominoes.h"

static std::vector<int> bag;
static std::mt19937 rng(std::random_device{}()); // RNG = Random Number Generator

// ============================ spawn shape =======================================
Shape *CreateShape(int type)
{
    switch (type)
    {
    case 0:
        return new Square();
    case 1:
        return new TShape();
    case 2:
        return new SShape();
    case 3:
        return new ZShape();
    case 4:
        return new LShape();
    case 5:
        return new JShape();
    case 6:
        return new line();
    }
    return new Square();
}
void RefillBag()
{
    bag = {0, 1, 2, 3, 4, 5, 6};
    shuffle(bag.begin(), bag.end(), rng);
}

Shape *SpawnShape()
{
    if (bag.empty())
        RefillBag();

    int type = bag.back();
    bag.pop_back();

    return CreateShape(type);
}
