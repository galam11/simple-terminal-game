#include "Location.h"

Location Location::down() const
{
    return Location(row + 1, col);
}

Location Location::up() const
{
    return Location(row - 1, col);
}

Location Location::right() const
{
    return Location(row, col + 1);
}

Location Location::left() const
{
    return Location(row, col - 1);
}