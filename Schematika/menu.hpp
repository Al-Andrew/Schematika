#pragma once
#include "sl.h"
#include "string"
#include "helpers.hpp"
#include "blocks.hpp"
#include <array>


/// <summary>
/// Struct to hold the data for the menu
/// </summary>
/// <author>Andrei</author>
struct Menu
{
    std::string name;
    double x = 0, y = 0;
    double width = 0, height = 0;
    std::vector<Block> displayBlocks;
    bool isClicked = false;
};

/// <summary>
/// Pseudo-constructor for the menu
/// </summary>
/// <returns>The menu(should be singleton)</returns>
Menu makeMenu();

/// <summary>
/// Draws the menu
/// </summary>
/// <param name="m">The menu struct</param>
void drawMenu(const Menu& m);

/// <summary>
/// Checks for updates in the menu
/// </summary>
/// <param name="m">The menu struct</param>
/// <param name="m">The global cooldown</param>
Type updateMenu(const Menu& m, double& cooldown);