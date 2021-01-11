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

	Node* n = new Node;
	//n->host = &b;
	n->x = b.x;
	n->y = b.y - b.height / 2.f;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;

	b.nodes.push_back(n);

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


	Node* n = new Node;
	//n->host = &b;
	n->x = b.x;
	n->y = b.y + b.height / 2.f;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;
	b.nodes.push_back(n);

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

	Node* m = new Node;
	//m->host = &b;
	m->x = b.x;
	m->y = b.y + b.height / 2;
	m->r = NODE_RADIUS;
	m->floating = false;
	m->next = nullptr;
	b.nodes.push_back(m);

	Node* n = new Node;
	//n->host = &b;
	n->x = b.x;
	n->y = b.y - b.height / 2;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;
	b.nodes.push_back(n);

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

	Node* m = new Node;
	//m->host = &b;
	m->x = b.x;
	m->y = b.y + b.height / 2;
	m->r = NODE_RADIUS;
	m->floating = false;
	m->next = nullptr;
	b.nodes.push_back(m);

	Node* n = new Node;
	//n->host = &b;
	n->x = b.x;
	n->y = b.y - b.height / 2;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;
	b.nodes.push_back(n);

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

	Node* m = new Node;
	//m->host = &b;
	m->x = b.x;
	m->y = b.y + b.height / 2.f;
	m->r = NODE_RADIUS;
	m->floating = false;
	m->next = nullptr;
	b.nodes.push_back(m);

	Node* n = new Node;
	//n->host = &b;
	n->x = b.x;
	n->y = b.y - b.height / 2.f;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;

	b.nodes.push_back(n);

	return b;
}

Block generateDecizie()
{
	Block b;
	b.type = Type::DECIZIE;
	b.x = DEFAULT_X;
	b.y = DEFAULT_Y;
	b.width = DECIZIE_WIDTH;
	b.height = DECIZIE_HEIGHT;
	b.floating = false;

	Node* n = new Node;
	//n->host = &b;
	n->x = b.x - b.width/2.f;
	n->y = b.y - b.height / 3.5;
	n->r = NODE_RADIUS;
	n->floating = false;
	n->next = nullptr;
	b.nodes.push_back(n);

	Node* m = new Node;
	//m->host = &b;
	m->x = b.x + b.width / 2.f;
	m->y = b.y - b.height / 3.5;
	m->r = NODE_RADIUS;
	m->floating = false;
	m->next = nullptr;
	b.nodes.push_back(m);

	Node* l = new Node;
	//l->host = &b;
	l->x = b.x;
	l->y = b.y + b.height / 2.5;
	l->r = NODE_RADIUS;
	l->floating = false;
	l->next = nullptr;
	b.nodes.push_back(l);
	return b;
}

void drawStart(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slCircleFill(b.x - 35, b.y, b.height / 2, 20);
	slRectangleFill(b.x, b.y, b.width - 40, b.height);
	slCircleFill(b.x + 35, b.y, b.height / 2, 20);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x, b.y - 10, "START");
}

void drawStop(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slCircleFill(b.x - 35, b.y, b.height / 2, 20);
	slRectangleFill(b.x, b.y, b.width - 40, b.height);
	slCircleFill(b.x + 35, b.y, b.height / 2, 20);
	setForeColor(BLOCK_TEXT_COLOR);
	slText(b.x, b.y - 10, "STOP");
}

void drawInput(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	double x = b.x - b.width / 2;
	double y1 = b.y - b.height / 2;
	double y2 = b.y + b.height / 2;
	for (int i = 0; i <b.width; i++)
	{
		slLine(x- 10 + i, y1 , x + 10 + i,y2);
	}
	setForeColor(BLOCK_TEXT_COLOR);
	std::string txt;
	if (b.text == "\0")
		txt = "IN";
	else
		txt = b.text;
	slText(b.x, b.y - 5, txt.c_str());
}

void drawOutput(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	double x = b.x - b.width / 2;
	double y1 = b.y - b.height / 2;
	double y2 = b.y + b.height / 2;
	for (int i = 0; i < b.width; i++)
	{
		slLine(x + 10 + i, y1, x - 10 + i, y2);
	}
	setForeColor(BLOCK_TEXT_COLOR);
	std::string txt;
	if (b.text == "\0")
		txt = "OUT";
	else
		txt = b.text;
	slText(b.x, b.y - 5, txt.c_str());
}

void drawCalcul(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slRectangleFill(b.x, b.y, b.width, b.height);
	setForeColor(BLOCK_TEXT_COLOR);
	std::string txt;
	if (b.text == "\0")
		txt = "CALCUL";
	else
		txt = b.text;
	slText(b.x, b.y - 10, txt.c_str());
}

void drawDecizie(const Block& b)
{
	setForeColor(BLOCK_FILL_COLOR);
	slTriangleFill(b.x, b.y + b.height /5 , b.width, b.height/2.5);
	slRectangleFill(b.x, b.y - (b.height - b.height/2.5)/2, b.width, b.height - b.height/2.5);
	setForeColor(BLOCK_DECIZIE_DA_COLOR);
	slRectangleFill(b.x - 10.5, b.y + 2, 21, 16);
	setForeColor(BLOCK_DECIZIE_NU_COLOR);
	slRectangleFill(b.x +  10.5, b.y + 2, 21, 16);
	slSetFontSize(13);
	setForeColor(BLOCK_DECIZIE_TEXT_COLOR);
	slText(b.x + 11, b.y - 2, "F");
	slText(b.x - 9, b.y - 2, "A");
	setForeColor(BLOCK_TEXT_COLOR);
	slSetFontSize(20);
	std::string txt;
	if (b.text == "\0")
		txt = "DECIZIE";
	else
		txt = b.text;
	slText(b.x, b.y - 24, txt.c_str());
}

void drawNode( Node* n)
{
	Color c;
	if (isMouseInCircle(n->x, n->y, n->r) && int(n->x) < WINDOW_WIDTH - SELECT_BLOCK_MENU_WIDTH)
		c = NODE_HOVER_COLOR;
	else
		c = NODE_COLOR;
	setForeColor(c);
	slCircleFill(n->x, n->y, n->r, 15);
	if (n->next != nullptr)
	{
		double difY = abs(n->y - n->next->y) / 4;
		double difX = abs(n->x - n->next->x) / 2;
		if (difY > 25)
			difY = 25;
		drawNode(n->next);
		setForeColor(NODE_LINE_COLOR);
		if (n->x == n->next->x)
			slLine(n->x, n->y, n->next->x, n->next->y);
		else if (n->host != nullptr && n->next->host == nullptr)
		{
			slLine(n->x, n->y, n->x, n->y - 15);
			slLine(n->x, n->y - 15, n->next->x, n->y - 15);
			n->next->y = n->y - 15;
		}
		else if (n->host == nullptr)
		{
				slLine(n->x, n->y, n->x, n->next->y);
				slLine(n->x, n->next->y, n->next->x, n->next->y);
		}
		else
		{	
			if (n->y > n->next->y)
			{	
					slLine(n->x, n->y, n->x, n->y - difY);
					slLine(n->x, n->y - difY, n->next->x, n->y - difY);
					slLine(n->next->x, n->y - difY, n->next->x, n->next->y);
			}
			else if (n->y <= n->next->y)
			{
				if (n->x < n->next->x)
				{
					slLine(n->next->x, n->next->y, n->next->x, n->next->y + difY);
					slLine(n->next->x, n->next->y + difY, n->next->x - difX, n->next->y + difY);
					slLine(n->next->x - difX, n->next->y + difY, n->next->x - difX, n->y - difY);
					slLine(n->next->x - difX, n->y - difY, n->x, n->y - difY);
					slLine(n->x, n->y - difY, n->x, n->y);
				}
				else
				{
					slLine(n->next->x, n->next->y, n->next->x, n->next->y + difY);
					slLine(n->next->x, n->next->y + difY, n->next->x + difX, n->next->y + difY);
					slLine(n->next->x + difX, n->next->y + difY, n->next->x + difX, n->y - difY);
					slLine(n->next->x + difX, n->y - difY, n->x, n->y - difY);
					slLine(n->x, n->y - difY, n->x, n->y);
				}
			}
		}
		if (isCircleClicked(n->x, n->y, n->r)) //disconnect the blocks
		{
			n->next = nullptr;
		}
	}  	
}

Block generate(Type t)
{
	switch (t)
	{
	case Type::START:
		return generateStart();
	case Type::CALCUL:
		return generateCalcul();
	case Type::DECIZIE:
		return generateDecizie();
	case Type::INPUT:
		return generateInput();
	case Type::OUTPUT:
		return generateOutput();
	case Type::STOP:
		return generateStop();
	}
	return generateStart();
}

void draw(const Block& b)
{
	slSetFontSize(TEXT_BLOCK_SIZE);
	slSetTextAlign(SL_ALIGN_CENTER);
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
		drawInput(b);
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
	for ( Node* n : b.nodes)
	{
		drawNode(n);
	}
}

void update(Block& b, double& cooldown)
{
	if (b.floating)
	{
		double oldX = b.x;
		double oldY = b.y;
		b.x = slGetMouseX();
		b.y = slGetMouseY();
		limitsOfFloatingBlocks(b);
		double dx = b.x - oldX;
		double dy = b.y - oldY;
		for (Node*& n : b.nodes)
		{
			n->x += dx;
			n->y += dy;
		}
		if (slGetKey(SL_KEY_ENTER) and cooldown <= slGetTime() and b.type != Type::START and b.type != Type::STOP)
		{
			warn("Please open console for input");
			std::cout << "Please enter the expression you want in this" << typeToString(b.type) << "block : \n";
			std::string expression;
			std::getline(std::cin,expression);
			b.text = expression;
			b.floating = false;
			double newWidth = slGetTextWidth(expression.c_str());
			if (b.width > newWidth)
			{
				if (b.type == Type::INPUT)
				{
					if (newWidth > IN_WIDTH)
						b.width = newWidth + 10;
					else
						b.width = IN_WIDTH;
				}
				else if (b.type == Type::OUTPUT)
				{
					if (newWidth > OUT_WIDTH)
						b.width = newWidth + 10;
					else
						b.width = OUT_WIDTH;
				}
				else if (b.type == Type::CALCUL)
				{
					if (newWidth > CALCUL_WIDTH)
						b.width = newWidth + 10;
					else
						b.width = CALCUL_WIDTH;
				}
				else if (b.type == Type::DECIZIE)
				{	
					double width = b.width;
					if (newWidth < DECIZIE_WIDTH)
					{
						b.width = DECIZIE_WIDTH;
					}
					else 
						b.width = newWidth + 15;
					for (Node*& n : b.nodes)
					{
						if (b.type == Type::DECIZIE && n->x != b.x)
						{
							if (n->x == b.x - width / 2)
							{
								n->x = b.x - b.width / 2;
							}
							else if (n->x == b.x + width / 2)
							{
								n->x = b.x + b.width / 2;
							}
						}
					}
				}
			}
			else if (b.width < newWidth)
			{	
					if (b.type == Type::DECIZIE )
					{	
						double width = b.width;
						b.width = newWidth + 15;
						for (Node*& n : b.nodes)
						{
							if (n->x != b.x)
							{
								if (n->x == b.x - width / 2)
								{
									n->x = b.x - b.width / 2;
								}
								else if (n->x == b.x + width / 2)
								{
									n->x = b.x + b.width / 2;
								}
							}
						}
					}
					else
						b.width = newWidth + 10;
			}

			setCooldown(cooldown);
		}
	}
	if (isRectClicked(b.x, b.y, b.width, b.height) and cooldown < slGetTime())
	{
		b.floating = !b.floating;
		setCooldown(cooldown);
	}
}

void updateNode(Node*& n, double& cooldown, clickHandler& handle)
{
	if (isCircleClicked(n->x, n->y, n->r) and cooldown < slGetTime())
	{
		if (n->next == nullptr)
		{
			if (handle.set)
			{
				handle.to = n;
			}
			else
			{
				handle.from = n;
				handle.set = true;
			}
		}
		else if(n->host == nullptr)
		{
			n->floating = !n->floating;
		}
		setCooldown(cooldown);
	}

	if (n->floating)
	{
		n->x = slGetMouseX();
		n->y = slGetMouseY();
	}

}

void handleDraw(const clickHandler& handle)
{
	if (handle.set == true and handle.to == nullptr)
	{
		Node* f = handle.from;
		setForeColor(NODE_SELECT_COLOR);
		slCircleFill(f->x, f->y, f->r, 15);
		double mx = slGetMouseX();
		double my = slGetMouseY();
		slCircleFill(mx, my, f->r, 15);
		setForeColor(NODE_LINE_COLOR);
		slLine(f->x, f->y, mx, my);
	}
}

void handleUpdate(double& cooldown, clickHandler& handle, std::vector<Node*>& nodes, unsigned int& nodeIdCounter)
{
	if (handle.set and handle.to != nullptr)
	{
		if (handle.to != handle.from)
		{
			handle.from->next = handle.to;
			handle.set = false;
			handle.from = nullptr;
			handle.to = nullptr;
		}
		else
		{
			handle.set = false;
			handle.from = nullptr;
			handle.to = nullptr;
		}
	}
	if (slGetMouseButton(SL_MOUSE_BUTTON_RIGHT) and cooldown <= slGetTime() and handle.set)
	{
		Node* d = new Node;
		d->x = slGetMouseX();
		d->y = slGetMouseY();
		d->r = handle.from->r;
		handle.from->next = d;
		handle.set = true;
		handle.from = d;
		handle.to = nullptr;
		d->id = nodeIdCounter;
		nodeIdCounter++;
		nodes.push_back(d);
		setCooldown(cooldown);
	}
}


