#include "sl.h"
#include "blocks.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include<iostream>


Block generateStart()
{
	Block b;
	b.type = Type::START;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = START_WIDTH;
	b.height = START_HEIGHT;
	b.floating = false;

	return b;
}

Block generateStop()
{
	Block b;
	b.type = Type::STOP;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = STOP_WIDTH;
	b.height = STOP_HEIGHT;
	b.floating = false;

	return b;
}

Block generateInput()
{
	Block b;
	b.type = Type::INPUT;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = IN_WIDTH;
	b.height = IN_HEIGHT;
	b.floating = false;

	return b;
}

Block generateOutput()
{
	Block b;
	b.type = Type::OUTPUT;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = OUT_WIDTH;
	b.height = OUT_HEIGHT;
	b.floating = false;

	return b;
}

Block generateCalcul()
{
	Block b;
	b.type = Type::CALCUL;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = CALCUL_WIDTH;
	b.height = CALCUL_HEIGHT;
	b.floating = false;

	return b;
}

Block generateDecizie()
{
	Block b;
	b.type = Type::DECIZIE;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = DECIZIE_HEIGHT;
	b.height = DECIZIE_HEIGHT;
	b.floating = false;

	return b;
}

void drawStart(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slCircleFill(b.x - 34, b.y, b.height / 2, 20);
	slRectangleFill(b.x, b.y, b.width - 30, b.height);
	slCircleFill(b.x + 34, b.y, b.height / 2, 20);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x + 5, b.y - 10, "START");
}

void drawStop(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slCircleFill(b.x - 34, b.y, b.height / 2, 20);
	slRectangleFill(b.x, b.y, b.width - 30, b.height);
	slCircleFill(b.x + 34, b.y, b.height / 2, 20);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x + 5, b.y - 10, "STOP");
}

void drawInput(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slRectangleFill(b.x, b.y, IN_WIDTH, IN_HEIGHT);
	slTriangleFill(b.x - 50, b.y, 40, IN_HEIGHT);
	setForeColor(BACKGROUND_COLOR);
	slTriangleFill(b.x + 50, b.y, 40, IN_HEIGHT);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x - 10, b.y + 15, "IN");
}

void drawOutput(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slRectangleFill(b.x, b.y, OUT_WIDTH, OUT_HEIGHT);
	slTriangleFill(b.x - 50, b.y, 40, OUT_HEIGHT);
	setForeColor(BACKGROUND_COLOR);
	slTriangleFill(b.x + 50, b.y, 40, OUT_HEIGHT);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x - 10, b.y + 15, "OUT");
}

void drawCalcul(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slRectangleFill(b.x, b.y, CALCUL_WIDTH, CALCUL_HEIGHT);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x, b.y - 10, "CALCUL");
}

void drawDecizie(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slTriangleFill(b.x, b.y, DECIZIE_WIDTH, DECIZIE_HEIGHT);
	setForeColor(BLOCK_DECIZIE_DA_COLOR);
	slRectangleFill(b.x - 55, b.y, 25, 25);
	slSetFontSize(15);
	setForeColor(BLOCK_DECIZIE_TEXT_COLOR);
	slText(b.x - 55, b.y - 5, "DA");
	setForeColor(BLOCK_DECIZIE_NU_COLOR);
	slRectangleFill(b.x + 55, b.y, 25, 25);
	setForeColor(BLOCK_DECIZIE_TEXT_COLOR);
	slText(b.x + 55, b.y - 5, "NU");
	setForeColor(BLOCK_TEXT_COLOR);
	slSetFontSize(20);
	slText(b.x, b.y - 20, "DECIZIE");
}

void draw(const Block& b)
{
	switch (b.type)
	{
	case Type::START:
		drawStart(b);
		break;
	case Type::CALCUL:
		drawCalcul(b);
		break;
	case Type::DECIZIE:
		drawDecizie(b);
		break;
	case Type::INPUT:
		drawDecizie(b);
		break;
	case Type::OUTPUT:
		drawOutput(b);
		break;
	case Type::STOP:
		drawStop(b);
		break;
	default:
		break;
	}
}

void update(Block& b, double& cooldown)
{
	if (b.floating)
	{
		b.x = slGetMouseX();
		b.y = slGetMouseY();
		limitsOfFloatingBlocks(b);
	}
	if (isRectClicked(b.x, b.y, b.width, b.height) and cooldown < slGetTime())
	{
		b.floating = !b.floating;
		setCooldown(cooldown);
	}
}