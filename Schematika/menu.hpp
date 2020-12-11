#pragma once
#include "sl.h"
#include "string"
#include "helpers.hpp"
#include "blocks.hpp"
#include <array>

struct Menu
{
	std::string name;
	double x = 0, y = 0;
	double width = 0, height = 0;
	std::array<Block,6> displayBlocks;
	bool isClicked = false;
};


void drawMenu(const Menu& m);
Menu makeMenu();