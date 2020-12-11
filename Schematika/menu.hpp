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
	std::vector<Block> displayBlocks;
	bool isClicked = false;
};


Menu makeMenu();
void drawMenu(const Menu& m);
Type updateMenu(const Menu& m, double& cooldown);