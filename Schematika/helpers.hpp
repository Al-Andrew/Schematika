#pragma once
#include "sl.h"
#include "config.hpp"
#include "blocks.hpp"
#include "menu.hpp"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

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
/// Increments the cooldown 
/// </summary>
/// <param name="cooldown"></param>
/// <author>Cristi</author>
void setCooldown(double& cooldown);

/// <summary>
/// Draws a bordered rectangle
/// </summary>
/// <param name="fill">Color to fill the rectangle</param>
/// <param name="bord">Color for the rectangle border</param>
/// <param name="x">coord of the block</param>
/// <param name="y">coord of the block</param>
/// <param name="w">width of the block</param>
/// <param name="h">height of the block</param>
/// <param name="bw">width of the border</param>
/// <author>Andrei</author>
void drawBorderedRect(const Color& fill, const Color& bord, const double x, const double y, const double w, const double h, const double bw);

/// <summary>
/// Checks if the node recieved as parameter overlaps with a node in the vector
/// </summary>
/// <param name="n">The node to check against the vector</param>
/// <param name="nodes">A vector containing all nodes</param>
/// <returns>A pointer to the overlaping node if it exists / nullptr otherwise</returns>
/// <author>Andrei</author>
Node* isOverlapingNode(const Node* n, const std::vector<Node*>& nodes);

void warn(std::string message);
std::string typeToString(Type t);

/// <summary>
/// Saves the project into a file
/// </summary>
/// <author>Andrei</author>
void saveToFile(std::vector<Block> blocks, std::vector<Node*> nodes);

/// <summary>
/// Opens the project from a saved file
/// </summary>
/// <author>Cristi and Andrei</author>
void openFile(std::vector<Block>& blocks, std::vector<Node*>& nodes,unsigned int & nodeIdCount);

/// <summary>
/// Deletes a block and its nodes
/// </summary>
/// <author>Cristi</author>
void deleteBlock(std::vector<Block>& blocks, std::vector<Node*>& nodes);

/// <summary>
/// Draws the  background of the window of the menu
/// </summary>
/// <author>Cristi</author>
void drawWindow( double x, double y, double width, double height);

/// <summary>
/// Draws the  background of the window of the submenu
/// </summary>
/// <author>Cristi</author>
void drawSubMenuWindow(double x, double y, double width, double height);
