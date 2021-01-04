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
	int Q2 = slLoadTexture("./Images/Q2.png");
	int q2 = slLoadTexture("./Images/Q2.1.png");
	int Qq2 = slLoadTexture("./Images/Q2.2.png");
	int Q3 = slLoadTexture("./Images/Q3.png");
	int q3 = slLoadTexture("./Images/Q3.1.png");
	int Q4 = slLoadTexture("./Images/Q4.png");
	int q4 = slLoadTexture("./Images/Q4.1.png");
	int Q5 = slLoadTexture("./Images/Q5.png");
	int q5 = slLoadTexture("./Images/Q5.2.png");
	int Qq5 = slLoadTexture("./Images/Q5.1.png");
	int qQ5 = slLoadTexture("./Images/Q5.3.png");
	double cooldown = 0;
	bool onTop = false; //for subMenu windows (prevent the clicking under the window)
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
		drawMenu(menu);
		slSprite(trash, static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH - SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT / 1.3, SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT);
		
		// Responsible for generating new blocks
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

		deleteBlock(blocks, nodes);

		//Responsible for the work of the buttons
		if (menuButtons u = updateMenu(menu,umenu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
				case menuButtons::New: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); std::vector<updatedMenu>().swap(upmenu); umenu.onTop = false; std::vector<updatedSubMenu>().swap(upsmenu); nodeIdCount = 1; onTop = false; break;
				case menuButtons::Save: saveToFile(blocks, nodes); std::vector<updatedMenu>().swap(upmenu); umenu.onTop = false; std::vector<updatedSubMenu>().swap(upsmenu); onTop = false; break;
				case menuButtons::Open: openFile(blocks, nodes, nodeIdCount); break;
				case menuButtons::Run: break;
				case menuButtons::NOT_A_BUTTON: break;
				default: break;
			}
		}
		if (menuButtons u = updateMenu(menu,umenu, cooldown); (u == menuButtons::Code || u == menuButtons::Help || u == menuButtons::About))
		{
				if (umenu.type == menuButtons::Help)//checks if the previous opened window was Help
				{
					std::vector<updatedSubMenu>().swap(upsmenu);
					onTop = false;
				}
				std::vector<updatedMenu>().swap(upmenu);
			upmenu.push_back(makeUpdatedMenu(u));
		}

		// Responsible for the work of the subMenu ( FAQ from Help window )
		if (helpQuestion u = updateSubMenu(umenu, usmenu, cooldown, onTop); u != helpQuestion::NOT_A_QUESTION && upmenu.back().type == menuButtons::Help)
		{
			upsmenu.push_back(makeQuestion(u));
			onTop = true;
		}

		// Responsible for the drawing of the blocks and updating the coordinates of the nodes
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

		// Responsible for the drawing and closing the window of the menu
		for (updatedMenu& a : upmenu)
		{	
			drawUpdatedMenu(a);
			if (isRectClicked(a.x+a.width/2-CLOSE_BUTTON_WIDTH/2, a.y+a.height/2 - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))//close button
			{
				std::vector<updatedMenu>().swap(upmenu);
				std::vector<updatedSubMenu>().swap(upsmenu);
				umenu.onTop = false;
				if(onTop)
					onTop = false;
			}
		}

		// Responsible for the drawing and closing the window of the subMenu ( FAQ from Help window )
		for (updatedSubMenu& a : upsmenu)
		{
			drawUpdatedSubMenu(a);
			switch(a.type)
			{
			case helpQuestion::Q1: slSprite(Q1,a.x - a.width / 3.1,a.y + a.height/4.4,120,260); slSprite(q1, a.x , 100, 420, 150); break;
				case helpQuestion::Q2: slSprite(Q2, a.x - a.width / 2.9, a.y + a.height / 3.3, 110, 170); slSprite(q2, a.x + a.width / 2.9, a.y + 35, 110, 170); slSprite(Qq2, a.x - a.width / 2.9, a.y -a.height/4, 110, 170); break;
				case helpQuestion::Q3: slSprite(Q3, a.x, a.y + a.height / 3.5, 350, 150); slSprite(q3, a.x, a.y - a.height/8, 420, 75); break;
				case helpQuestion::Q4: slSprite(Q4, a.x - a.width/3.6, a.y + a.height / 3.3, 160, 150); slSprite(q4, a.x, a.y - 75, 450, 75); break;
				case helpQuestion::Q5: slSprite(Q5, a.x - a.width/6.4, a.y + a.height / 2.5, 300, 45); slSprite(q5, a.x, a.y+ a.height/5, 450, 75); slSprite(Qq5, a.x - a.width / 6.4, a.y - 33, 300, 45); slSprite(qQ5, a.x, a.y - a.height / 3.5, 450, 60); break;
				case helpQuestion::Q6: break;
				default: break;
			}
			if (isRectClicked(830, 672.5, 50, 35))//back button
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