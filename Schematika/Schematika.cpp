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
	while (!slShouldClose())
	{
		drawBlocksMenu(bmenu);
		if (Type u = updateBlockMenu(bmenu, cooldown); u != Type::NOT_A_BLOCK)
		{
			blocks.push_back(generate(u));
			for (Node* n : blocks.back().nodes)
				nodes.push_back(n);
		}
		drawMenu(menu);
		for (Block& bl : blocks)
		{
			draw(bl);
			update(bl, cooldown);
		}
		for (int i = 0, st = nodes.size(); i < st; i++)
		{
			updateNode(nodes[i], nodes, cooldown, handle);
		}
		for (auto b : menu.buttons)
		{
			if (isRectClicked(b.x, b.y, b.width, b.height) && b.type == menuButtons::New)
			{
				blocks.clear();
			}
			else if (isRectClicked(b.x, b.y, b.width, b.height) && b.type == menuButtons::Save)
			{
				saveToFile(blocks, nodes);
			}
		}
		handleDraw(handle);
		handleUpdate(cooldown, handle, nodes);
		slText(100, 100, std::to_string(1 / slGetDeltaTime()).c_str());
		slRender();
	}
	slClose();
	return 0;
}