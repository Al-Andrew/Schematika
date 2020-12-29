#include "Schematika.hpp"

int main()
{
	slWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	setBackColor(BACKGROUND_COLOR);
	slSetFont(slLoadFont("./res/Fonts/OpenSans-Regular.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	int trash = slLoadTexture("./Images/Trash.png");
	int Q1 = slLoadTexture("./Images/Q1.png");
	int q1 = slLoadTexture("./Images/Q1.1.png");
	double cooldown = 0;
	bool onTop = false;
	clickHandler handle;
	BlockMenu bmenu = makeBlockMenu();
	Menu menu = makeMenu();
	updatedMenu umenu = makeUpdatedMenu(menuButtons());
	updatedSubMenu usmenu = makeQuestion(helpQuestion());
	unsigned int nodeIdCount = 1;
	std::vector<Block> blocks;
	std::vector<Node*> nodes;
	std::vector<updatedMenu> upmenu;
	std::vector<updatedSubMenu> upsmenu;
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
		slSprite(trash, static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH - SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT/1.3, SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT);
		if (menuButtons u = updateMenu(menu,umenu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
				case menuButtons::New: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); std::vector<updatedMenu>().swap(upmenu); std::vector<updatedSubMenu>().swap(upsmenu); nodeIdCount = 1; onTop = false; break;
				case menuButtons::Save: saveToFile(blocks, nodes); std::vector<updatedMenu>().swap(upmenu); std::vector<updatedSubMenu>().swap(upsmenu);onTop = false; break;
				case menuButtons::Open: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); std::vector<updatedMenu>().swap(upmenu); std::vector<updatedSubMenu>().swap(upsmenu); onTop = false; openFile(blocks,nodes, nodeIdCount); break;
				case menuButtons::Run: break;
				case menuButtons::NOT_A_BUTTON: break;
				default: break;
			}
		}

		if (menuButtons u = updateMenu(menu,umenu, cooldown); (u == menuButtons::Code || u == menuButtons::Help || u == menuButtons::About))
		{
			if (upmenu.size() > 2)
			{
				if (umenu.type == menuButtons::Help)
				{
					std::vector<updatedSubMenu>().swap(upsmenu);
					onTop = false;
				}
				std::vector<updatedMenu>().swap(upmenu);
			}
			upmenu.push_back(makeUpdatedMenu(u));
		}

		if (helpQuestion u = updateSubMenu(umenu, usmenu, cooldown, onTop); u != helpQuestion::NOT_A_QUESTION && upmenu.back().type == menuButtons::Help)
		{
			upsmenu.push_back(makeQuestion(u));
			onTop = true;
		}
		for (Block& bl : blocks)
		{
			draw(bl);
			if(umenu.onTop==false)
				update(bl, cooldown);
		}
		for (Node*& nd : nodes)
		{
			updateNode(nd, cooldown, handle);
		}
		for (updatedMenu& a : upmenu)
		{	
			drawUpdatedMenu(a);
			if (isRectClicked(a.x+a.width/2-CLOSE_BUTTON_WIDTH/2, a.y+a.height/2 - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))
			{
				std::vector<updatedMenu>().swap(upmenu);
				std::vector<updatedSubMenu>().swap(upsmenu);
				umenu.onTop = false;
				if(onTop)
					onTop = false;
			}
		}
		for (updatedSubMenu& a : upsmenu)
		{
			drawUpdatedSubMenu(a);
			switch(a.type)
			{
			case helpQuestion::Q1: slSprite(Q1,a.x - a.width / 3.1,a.y + a.width/3,120,260); slSprite(q1, a.x , 100, 420, 150); break;
				case helpQuestion::Q2: break;
				case helpQuestion::Q3: break;
				case helpQuestion::Q4: break;
				case helpQuestion::Q5: break;
				default: break;
			}
			if (isRectClicked(830, 672.5, 50, 35))
			{
				std::vector<updatedSubMenu>().swap(upsmenu);
				onTop = false;
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