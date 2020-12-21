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
	std::vector<updatedMenu> upmenu;
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
				nodes.push_back(n);
			}
		}
		drawMenu(menu);
		deleteBlock(blocks, nodes);
		slSprite(trash, static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH - SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT/1.3, SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT);
		if (menuButtons u = updateMenu(menu,umenu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
			case menuButtons::New: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); std::vector<updatedMenu>().swap(upmenu); nodeIdCount = 1; break;
				case menuButtons::Save: saveToFile(blocks, nodes); break;
				case menuButtons::Open: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); openFile(blocks,nodes, nodeIdCount); break;
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