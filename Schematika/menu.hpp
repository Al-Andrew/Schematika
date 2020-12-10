#pragma once
#include "sl.h"
#include "string"
struct Menu
{
    std::string name;
    int x, y;
    int width, height;
    bool isClicked = false;
};
