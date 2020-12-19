#include "Schematika.hpp"

int main()
{
	slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	setBackColor(BACKGROUND_COLOR);
	slSetFont(slLoadFont("./res/Fonts/OpenSans-Regular.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	int trash = slLoadTexture("./Trash.png");
	double cooldown = 0;
	clickHandler handle;
	BlockMenu bmenu = makeBlockMenu();
	Menu menu = makeMenu();
	updatedMenu umenu = makeUpdatedMenu(menuButtons());
	unsigned int nodeIdCount = 1;
	std::vector<Block> blocks;
	std::vector<Node*> nodes;
	std::vector<updatedMenu> umenu;
	blocks.reserve(100);
	while (!slShouldClose())
	{	
		drawBlocksMenu(bmenu);
		if (Type u = updateBlockMenu(bmenu, umenu, cooldown); u != Type::NOT_A_BLOCK)
		{
			blocks.push_back(generate(u));
			for (Node*& n : blocks.back().nodes)
			{
				n->id = nodeIdCount;
				nodeIdCount++;
				n->host = &blocks[blocks.size()-1];
				nodes.push_back(n);
			}
		}
		drawMenu(menu);
		deleteBlock(blocks, nodes);
		slSprite(trash, SELECT_TRASH_POSX, SELECT_TRASH_POSY, 40, 40);
		if (menuButtons u = updateMenu(menu,umenu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
				case menuButtons::New: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); std::vector<updatedMenu>().swap(upmenu); break;
				case menuButtons::Save: saveToFile(blocks, nodes); break;
				case menuButtons::Open: openFile(); std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); break;
				case menuButtons::Run: break;
				case menuButtons::NOT_A_BUTTON: break;
				default: break;
			}
		}
		if (menuButtons u = updateMenu(menu,umenu, cooldown); (u == menuButtons::Code || u == menuButtons::Help || u == menuButtons::About))
		{
			upmenu.push_back(makeUpdatedMenu(u));
		}
		for (Block& bl : blocks)
		{
			draw(bl);
			update(bl, cooldown);
		}
		for (Node*& nd : nodes)
		{
			updateNode(nd, cooldown, handle);
		}
		for (updatedMenu& a : upmenu)
		{
			drawUpdatedMenu(a);
			if (isRectClicked(a.x+a.width/2-CLOSE_BUTTON_WIDTH/2, a.y+a.height/2 - CLOSE_BUTTON_WIDTH / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))
			{
				std::vector<updatedMenu>().swap(upmenu);
				umenu.onTop = false;
			}


		}
		handleDraw(handle);
		handleUpdate(cooldown, handle, nodes, nodeIdCount);
		slText(100, 100, std::to_string(1 / slGetDeltaTime()).c_str());
		slRender();
	}
	slClose();
	return 0;
}