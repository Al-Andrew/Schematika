#pragma once
#include "sl.h"
#include "config.hpp"
#include "blocks.hpp"
#include <cstdint>
#include <cmath>

struct Color
{
    uint8_t r,g,b;
    float a = 1;
};

bool isCircleClicked(double x, double y, double r);
bool isRectClicked(double x, double y, double width,double height);
bool isMouseInRect(double x, double y, double width,double height);
bool isMouseInCircle(double x, double y, double r);
bool isCircleInCircle(double x1, double y1, double r1, double x2, double y2, double r2);
void limitsOfFloatingBlocks(Block& b);
void setCooldown(double& cooldown);