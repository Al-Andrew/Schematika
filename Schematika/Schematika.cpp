#include "Schematika.hpp"

int main()
{
	slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	setBackColor(BACKGROUND_COLOR);
	slSetFont(slLoadFont("./res/Fonts/OpenSans-Regular.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	double cooldown = 0;
	clickHandler handle;
	BlockMenu bmenu = makeBlockMenu();
	Menu menu = makeMenu();
	std::vector<Block> blocks;
	std::vector<Node*> nodes;
	std::vector<Button>buttons;
	while (!slShouldClose())
	{
		drawMenu(bmenu, menu);
		if (Type u = updateMenu(bmenu, cooldown); u != Type::NOT_A_BLOCK)
		{
			blocks.push_back(generate(u));
			for (Node* n : blocks.back().nodes)
				nodes.push_back(n);
		}

		for (Block& bl : blocks)
		{
			draw(bl);
			update(bl, cooldown);
		}
		for (int i = 0, st = nodes.size(); i < st; i++)
		{
			updateNode(nodes[i], nodes, cooldown, handle);
		}
		handleDraw(handle);
		handleUpdate(cooldown, handle, nodes);
		slRender();
	}
	slClose();
	return 0;
}