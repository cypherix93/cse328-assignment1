#include "Pixel.h"

using namespace Drawing;

Pixel::Pixel(int x, int y)
{
    X = x;
    Y = y;
}

Pixel::~Pixel()
{
}

bool Drawing::operator==(const Pixel left, const Pixel right)
{
    return left.X == right.X && left.Y == right.Y;
}

bool Drawing::operator!=(const Pixel left, const Pixel right)
{
    return !(left == right);
}
