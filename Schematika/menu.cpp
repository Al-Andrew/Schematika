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
	b.isClicked = false;

	double y = static_cast<double>(WINDOW_HEIGHT) - MENU_BORDER_WIDTH - START_HEIGHT / 2.f - SELECT_MENU_SPACER;
	b.displayBlocks[0] = generateStart();
	b.displayBlocks[0].x =b.x;
	b.displayBlocks[0].y = y;
	y -= MENU_BORDER_WIDTH + START_HEIGHT / 2.f + STOP_HEIGHT / 2.f + SELECT_MENU_SPACER;
	b.displayBlocks[1] = generateStop();
	b.displayBlocks[1].x = b.x;
	b.displayBlocks[1].y = y;
	y -= MENU_BORDER_WIDTH + STOP_HEIGHT / 2.f + IN_HEIGHT / 2.f + SELECT_MENU_SPACER;
	b.displayBlocks[2] = generateInput();
	b.displayBlocks[2].x = b.x;
	b.displayBlocks[2].y = y;
	y -= MENU_BORDER_WIDTH + IN_HEIGHT / 2.f + OUT_HEIGHT / 2.f + SELECT_MENU_SPACER;
	b.displayBlocks[3] = generateOutput();
	b.displayBlocks[3].x = b.x;
	b.displayBlocks[3].y = y;
	y -= MENU_BORDER_WIDTH + OUT_HEIGHT / 2.f + DECIZIE_HEIGHT / 2.f + SELECT_MENU_SPACER;
	b.displayBlocks[4] = generateDecizie();
	b.displayBlocks[4].x = b.x;
	b.displayBlocks[4].y = y;
	y -= MENU_BORDER_WIDTH + DECIZIE_HEIGHT / 2.f + CALCUL_HEIGHT / 2.f + SELECT_MENU_SPACER;
	b.displayBlocks[5] = generateCalcul();
	b.displayBlocks[5].x = b.x;
	b.displayBlocks[5].y = y;

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