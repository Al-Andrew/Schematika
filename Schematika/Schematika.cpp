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
	unsigned int nodeIdCount = 1;
	std::vector<Block> blocks;
	std::vector<Node*> nodes;
	while (!slShouldClose())
	{	
		drawBlocksMenu(bmenu);
		if (Type u = updateBlockMenu(bmenu, cooldown); u != Type::NOT_A_BLOCK)
		{
			blocks.push_back(generate(u));
			for (Node*& n : blocks.back().nodes)
			{
				n->id = nodeIdCount;
				nodeIdCount++;
				nodes.push_back(n);
			}
		}
		drawMenu(menu);
		slSprite(slLoadTexture("./Trash.png"), SELECT_TRASH_POSX, SELECT_TRASH_POSY, 40, 40);
		if (menuButtons u = updateMenu(menu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
			case menuButtons::New: blocks.clear(); break;
			case menuButtons::Save: saveToFile(blocks, nodes); break;
			case menuButtons::Open: openFile(); break;
			case menuButtons::Run: break;
			case menuButtons::Code: break;
			case menuButtons::Help: break;
			case menuButtons::About: break;
			case menuButtons::NOT_A_BUTTON:break;
			default: break;
			}
		}
		for (Block& bl : blocks)
		{
			draw(bl);
			update(bl, cooldown);
		}
		deleteBlock(blocks);
		for (Node*& nd : nodes)
		{
			updateNode(nd, cooldown, handle);
		}
		handleDraw(handle);
		handleUpdate(cooldown, handle, nodes, nodeIdCount);
		slText(100, 100, std::to_string(1 / slGetDeltaTime()).c_str());
		slRender();
	}
	slClose();
	return 0;
}