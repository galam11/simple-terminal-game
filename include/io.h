#pragma once

#include "Location.h"

namespace Keys
{
constexpr int ESCAPE = 27;
constexpr int SPECIAL_KEY = 224;
}

namespace SpecialKeys
{
constexpr int UP = 72;
constexpr int DOWN = 80;
constexpr int LEFT = 75;
constexpr int RIGHT = 77;
constexpr int SPACE_BAR = 32;
}

namespace Screen
{
void resetLocation();
void setLocation(const Location& location);
}
