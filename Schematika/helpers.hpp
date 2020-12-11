#pragma once
#include "sl.h"
#include "config.hpp"
#include "blocks.hpp"
#include <cstdint>
#include <cmath>

/// <summary>
/// Struct to hold color data
/// </summary>
struct Color
{
	unsigned short r = 0, g = 0, b = 0;
	double a = 1.f;
};

/// <summary>
/// Wraper to set the foreground color using our Color struct
/// </summary>
/// <param name="c">color to be set as foreground</param>
/// <author>Andrei</author>
void setForeColor(const Color& c);

/// <summary>
/// Wraper to set the background color using our Color struct
/// </summary>
/// <param name="c">color to be set as background</param>
void setBackColor(const Color& c);

/// <summary>
/// Helper function to determine if the mouse hovers over a given rectangle
/// </summary>
/// <param name="x">coord of the given rectangle</param>
/// <param name="y">coord of the given rectangle</param>
/// <param name="width">of the given rectangle</param>
/// <param name="height">of the given rectangle</param>
/// <returns>Bool whether the rectangle is hovered or not</returns>
/// <author>Andrei</author>
bool isMouseInRect(double x, double y, double width, double height);

/// <summary>
/// Helper function to determine if the mouse clicked on a given rectangle
/// </summary>
/// <param name="x">coord of the given rectangle</param>
/// <param name="y">coord of the given rectangle</param>
/// <param name="width">of the given rectangle</param>
/// <param name="height">of the given rectangle</param>
/// <returns>Bool whether the rectangle was clicked or not</returns>
/// <author>Cristi</author>
bool isRectClicked(double x, double y, double width, double height);

/// <summary>
/// Helper function to determine if the mouse hovers over a given circle
/// </summary>
/// <param name="x">coord of the given circle</param>
/// <param name="y">coord of the given circle</param>
/// <param name="r">of the given circle</param>
/// <returns>Bool whether the circle is hovered or not</returns>
/// <author>Andrei</author>
bool isMouseInCircle(double x, double y, double r);

/// <summary>
/// Helper function to determine if the mouse clicked on a given circle
/// </summary>
/// <param name="x">coord of the given circle</param>
/// <param name="y">coord of the given circle</param>
/// <param name="r">of the given circle</param>
/// <returns>Bool whether the circle is clicked or not</returns>
/// <author>Cristi</author>
bool isCircleClicked(double x, double y, double r);

/// <summary>
/// Helper function to determine if two circles are coliding
/// </summary>
/// <param name="x1">coord of the first circle</param>
/// <param name="y1">coord of the first circle</param>
/// <param name="r1">of the first circle</param>
/// <param name="x2">coord of the second circle</param>
/// <param name="y2">coord of the second circle</param>
/// <param name="r2">of the second circle</param>
/// <returns>Bool whether the circles are coliding or not</returns>
/// <author>Andrei</author>
bool isCircleInCircle(double x1, double y1, double r1, double x2, double y2, double r2);

/// <summary>
/// Makes sure the given block is within the bounds of the window
/// </summary>
/// <param name="b">- block to bound</param>
/// <author>Cristi</author>
void limitsOfFloatingBlocks(Block& b);

/// <summary>
/// Increments the cooldown to sync actions in the window
/// </summary>
/// <param name="cooldown"></param>
/// <author>Cristi</author>
void setCooldown(double& cooldown);


void drawBorderedRect(const Color& fill, const Color& bord, const double x, const double y, const double w, const double h, const double bw);