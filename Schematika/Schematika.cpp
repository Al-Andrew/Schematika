#include "Schematika.hpp"

void autoClosingofWindows(std::vector<updatedMenu>& upmenu, std::vector<updatedSubMenu>& upsmenu, updatedMenu& umenu, bool& onTop);

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
	int Q6 = slLoadTexture("./Images/Q6.png");
	int q6 = slLoadTexture("./Images/Q6_example.png");
	int Qq6 = slLoadTexture("./Images/Q6.1.png");
	int qQ6 = slLoadTexture("./Images/Q6.2.png");
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

	std::ofstream code;

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
		}//end

		deleteBlock(blocks, nodes);
		//Responsible for the work of the buttons
		if (menuButtons u = updateMenu(menu,umenu, cooldown); u != menuButtons::NOT_A_BUTTON)
		{
			switch (u)
			{
			case menuButtons::New: std::vector<Block>().swap(blocks); std::vector<Node*>().swap(nodes); autoClosingofWindows(upmenu, upsmenu, umenu, onTop); nodeIdCount = 1; break;
				case menuButtons::Save: saveToFile(blocks, nodes); autoClosingofWindows(upmenu, upsmenu, umenu, onTop); break;
				case menuButtons::Open: autoClosingofWindows(upmenu, upsmenu, umenu, onTop); openFile(blocks, nodes); break;
				case menuButtons::Run: autoClosingofWindows(upmenu, upsmenu, umenu, onTop); if (is_valid(blocks)) { saveToFile(blocks, nodes, "run.txt"); openFile(blocks, nodes, "run.txt"); interpret(blocks); } else umenu.onTop = true; break;
				case menuButtons::Code: if (is_valid(blocks)) { code.open("code.txt"); code << translate(blocks) << std::endl; code.close(); } else umenu.onTop = true; break;
				case menuButtons::NOT_A_BUTTON: break;
				default: break;
			}
		}
		if (menuButtons u = updateMenu(menu,umenu, cooldown); (u == menuButtons::Code || u == menuButtons::Help || u == menuButtons::About || u == menuButtons::Run))
		{
				if (umenu.type == menuButtons::Help && upsmenu.size()> 0) //checks if the previous opened window was Help and if it was opened a FAQ
				{
					std::vector<updatedSubMenu>().swap(upsmenu);
					onTop = false;
				}
			std::vector<updatedMenu>().swap(upmenu);
			if(!(u == menuButtons::Run && is_valid(blocks)))
				upmenu.push_back(makeUpdatedMenu(u));
		}//end

		// Responsible for the work of the subMenu ( FAQ from Help window )
		if (helpQuestion u = updateSubMenu(umenu, usmenu, cooldown, onTop); u != helpQuestion::NOT_A_QUESTION && upmenu.back().type == menuButtons::Help)
		{
			upsmenu.push_back(makeQuestion(u));
			onTop = true;
		}//end

		// Responsible for the drawing of the blocks and updating the coordinates of the nodes
		for (Block& bl : blocks)
		{
			draw(bl);
			if(umenu.onTop==false)
				update(bl, cooldown);
		}
		for (Node*& nd : nodes)
		{	
			if (umenu.onTop == false)
				updateNode(nd, cooldown, handle);
		}//end

		// Responsible for the drawing and closing the window of the menu
		for (updatedMenu& a : upmenu)
		{	
			drawUpdatedMenu(a,blocks);
			if (isRectClicked(a.x+a.width/2-CLOSE_BUTTON_WIDTH/2, a.y+a.height/2 - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))//close button
			{
				std::vector<updatedMenu>().swap(upmenu);
				std::vector<updatedSubMenu>().swap(upsmenu);
				umenu.onTop = false;
				if(onTop)
					onTop = false;
			}
		}//end

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
				case helpQuestion::Q6: slSprite(q6, a.x - a.width / 3.1, a.y + a.height / 4.0, 150, 260); slSprite(Q6, a.x + a.width / 6.4, a.y + 15, 300, 45); slSprite(Qq6, a.x - a.width / 6.3, a.y - a.height /5.5 , 300, 45); slSprite(qQ6, a.x + a.width / 4.2, 75, 220, 60); break;
				case helpQuestion::Q7: break;
				default: break;
			}
			if (isRectClicked(a.x - a.width/2 + BACK_BUTTON_WIDTH/2, a.y + a.height/2 - SELECT_MENU_HEIGHT/2, BACK_BUTTON_WIDTH, SELECT_MENU_HEIGHT))//back button
			{
				std::vector<updatedSubMenu>().swap(upsmenu);
				onTop = false;
			}
		}//end
		handleDraw(handle);
		handleUpdate(cooldown, handle, nodes, nodeIdCount);
		slRender();
	}
	slClose();
	return 0;
}

//Responsible for auto closing of windows, when clicking on another button of menu (New, Save, Open, Run).
void autoClosingofWindows(std::vector<updatedMenu>& upmenu, std::vector<updatedSubMenu>& upsmenu, updatedMenu& umenu, bool& onTop)
{
	if (upmenu.size() > 0)
	{
		std::vector<updatedMenu>().swap(upmenu);
		umenu.onTop = false;
	}
	 if (upsmenu.size() > 0)
	{
		std::vector<updatedSubMenu>().swap(upsmenu);
		onTop = false;
	}
}//end