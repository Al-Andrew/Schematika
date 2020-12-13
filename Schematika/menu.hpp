#pragma once
#include "sl.h"
#include "string"
#include "helpers.hpp"
#include "blocks.hpp"
#include <array>


/// <summary>
/// Struct to hold the data for the Block menu
/// </summary>
/// <author>Andrei</author>
struct BlockMenu
{
    std::string name;
    double x = 0, y = 0;
    double width = 0, height = 0;
    std::vector<Block> displayBlocks;
    bool isClicked = false;
};
/// <summary>
/// Struct to hold the data for the submenu
/// </summary>
/// <author>Cristi</author>
struct subMeniu
{
    std::string name;
    double width = 0, height = 0;
    double x = 0, y = 0;
};
/// <summary>
/// Struct to hold the data for the bottons of the menu
/// </summary>
/// <author>Cristi and Andrei</author>
struct Button
{
    std::string name;
    double width=0, height=0;
    double x=0, y=0;
    bool isClicked=false;
};
/// <summary>
/// Struct to hold the data for the  menu
/// </summary>
/// <author>Cristi</author>
struct Menu
{
    double x = 0, y = 0;
    double width = 0, height = 0;
    std::vector<Button> buttons;
    std::vector<subMeniu> submeniu;
};
/// <summary>
/// Pseudo-constructor for the Block menu
/// </summary>
/// <returns>The Block menu(should be singleton)</returns>
/// <author>Andrei</author>
BlockMenu makeBlockMenu();

/// <summary>
/// Pseudo-constructor for the  menu
/// </summary>
/// <returns>The menu(should be singleton)</returns>
/// <author>Cristi and Andrei</author>
Menu makeMenu();

/// <summary>
/// Draws the menu
/// </summary>
/// <param name="m">The menu struct</param>
/// <author>Cristi and Andrei</author>
void drawMenu(const BlockMenu& m, const Menu& n);

/// <summary>
/// Checks for updates in the menu
/// </summary>
/// <param name="m">The menu struct</param>
/// <param name="m">The global cooldown</param>
/// <author>Andrei</author>
Type updateMenu(const BlockMenu& m, double& cooldown);

/// <summary>
/// Pseudo-constructor for the  menu
/// </summary>
/// <returns>The button(should be singleton)</returns>
/// <author>Andrei and Cristi</author>
Button makeButton(std::string name, double width, double height, double x, double y);

/// <summary>
/// Draws the button
/// </summary>
/// <param name="m">The button struct</param>
/// <author>Cristi</author>
void drawButton(const Button& m);
