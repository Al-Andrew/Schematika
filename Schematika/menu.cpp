#include "blocks.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "menu.hpp"
#include "sl.h"

Menu makeMenu()
{
	Menu b;
	b.x = static_cast<double>(WINDOW_WIDTH) - SELECT_MENU_WIDTH / 2.f;
	b.y = static_cast<double>(WINDOW_HEIGHT) / 2.f;
	b.width = SELECT_MENU_WIDTH;
	b.height = SELECT_MENU_HEIGHT;
	
	double y = static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_SPACER / 2.f;
	for (auto t : allTypes)
	{
		b.displayBlocks.push_back(generate(t));
		b.displayBlocks.back().y = y;
		b.displayBlocks.back().x = b.x;
		y -= SELECT_MENU_SPACER;
	}
	

	return b;
}

void drawMenu(const Menu& m)
{
	drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, m.x, m.y, m.width, m.height, MENU_BORDER_WIDTH);
	for (Block bl : m.displayBlocks)
	{
		draw(bl);
	}
}

Type updateMenu(const Menu& m, double& cooldown)
{
	double cpy = cooldown;
	for (Block bl : m.displayBlocks)
	{
		update(bl,cooldown);
		if (cpy != cooldown)
			return bl.type;
	}
	return Type::NOT_A_BLOCK;
}