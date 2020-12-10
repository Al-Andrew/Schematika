#include "blocks.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "menu.hpp"
#include "sl.h"

Menu generateInitialStart()
{	
	Menu b;
	b.x = 1205;
	b.y = 590;
	b.width = START_WIDTH;
	b.height = START_HEIGHT;
	b.isClicked = false;

	return b;
}