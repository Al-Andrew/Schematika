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
    n->host = &b;
    n->x = b.x;
    n->y = b.y - b.height/2.f;
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
    n->host = &b;
    n->x = b.x;
    n->y = b.y + b.height/2.f;
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

    Node* n = new Node;
    n->host = &b;
    n->x = b.x;
    n->y = b.y - b.height / 2;
    n->r = NODE_RADIUS;
    n->floating = false;
    n->next = nullptr;
    b.nodes.push_back(n);

    Node* m = new Node;
    m->host = &b;
    m->x = b.x;
    m->y = b.y + b.height/2;
    m->r = NODE_RADIUS;
    m->floating = false;
    n->next = nullptr;
    b.nodes.push_back(m);

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

    Node* n = new Node;
    n->host = &b;
    n->x = b.x;
    n->y = b.y - b.height / 2;
    n->r = NODE_RADIUS;
    n->floating = false;
    n->next = nullptr;
    b.nodes.push_back(n);

    Node* m = new Node;
    m->host = &b;
    m->x = b.x;
    m->y = b.y + b.height/2;
    m->r = NODE_RADIUS;
    m->floating = false;
    m->next = nullptr;
    b.nodes.push_back(m);

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

    Node* n = new Node;
    n->host = &b;
    n->x = b.x;
    n->y = b.y - b.height/2.f;
    n->r = NODE_RADIUS;
    n->floating = false;
    n->next = nullptr;

    b.nodes.push_back(n);

    Node* m = new Node;
    m->host = &b;
    m->x = b.x;
    m->y = b.y + b.height/2.f;
    m->r = NODE_RADIUS;
    m->floating = false;
    m->next = nullptr;
    b.nodes.push_back(m);

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
    n->host = &b;
    n->x = b.x-b.width/2;
    n->y = b.y - b.height/2.f;
    n->r = NODE_RADIUS;
    n->floating = false;
    n->next = nullptr;
    b.nodes.push_back(n);

    Node* m = new Node;
    m->host = &b;
    m->x = b.x+b.width/2;
    m->y = b.y - b.height/2.f;
    m->r = NODE_RADIUS;
    m->floating = false;
    m->next = nullptr;
    b.nodes.push_back(m);

    Node* l = new Node;
    l->host = &b;
    l->x = b.x;
    l->y = b.y + b.height/2.f;
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
    slText(b.x , b.y - 10, "START");
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
    for(int i=0;i<IN_WIDTH;i++)
    {
        slLine(b.x-60 +i, b.y- b.height / 2, b.x-40+i, b.y+b.height/2);
    }
    setForeColor(BLOCK_TEXT_COLOR);
    slText(b.x , b.y - 5, "IN");
}

void drawOutput(const Block& b)
{
    setForeColor(BLOCK_FILL_COLOR);
    for(int i=0;i<OUT_WIDTH;i++)
    {
        slLine(b.x-60 +i, b.y- b.height / 2, b.x-40+i, b.y+b.height/2);
    }
    setForeColor(BLOCK_TEXT_COLOR);
    slText(b.x , b.y - 5, "OUT");
}

void drawCalcul(const Block& b)
{
    setForeColor(BLOCK_FILL_COLOR);
    slRectangleFill(b.x, b.y, b.width, b.height);
    setForeColor(BLOCK_TEXT_COLOR);
    slText(b.x, b.y - 10, "CALCUL");
}

void drawDecizie(const Block& b)
{
    setForeColor(BLOCK_FILL_COLOR);
    slTriangleFill(b.x, b.y, b.width, b.height);
    setForeColor(BLOCK_DECIZIE_DA_COLOR);
    slRectangleFill(b.x - 55, b.y, 25, 25);
    slSetFontSize(15);
    setForeColor(BLOCK_DECIZIE_TEXT_COLOR);
    slText(b.x - 55, b.y - 5, "A");
    setForeColor(BLOCK_DECIZIE_NU_COLOR);
    slRectangleFill(b.x + 55, b.y, 25, 25);
    setForeColor(BLOCK_DECIZIE_TEXT_COLOR);
    slText(b.x + 55, b.y - 5, "F");
    setForeColor(BLOCK_TEXT_COLOR);
    slSetFontSize(20);
    slText(b.x, b.y - 20, "DECIZIE");
}

void drawNode(Node* n)
{
    Color c;
    if (isMouseInCircle(n->x, n->y, n->r) && int(n->x) < WINDOW_WIDTH - SELECT_BLOCK_MENU_WIDTH)
        c = NODE_HOVER_COLOR;
    else
        c = NODE_COLOR;
    
    setForeColor(c);
    slCircleFill(n->x, n->y, n->r, 50);
    if (n->next != nullptr)
    {
        drawNode(n->next);
        setForeColor(NODE_LINE_COLOR);
        slLine(n->x, n->y, n->next->x, n->next->y);
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
    for (Node* n : b.nodes)
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
    }
    if (isRectClicked(b.x, b.y, b.width, b.height) and cooldown < slGetTime())
    {
        b.floating = !b.floating;
        setCooldown(cooldown);
    }
}

void updateNode(Node*& n,std::vector<Node*>& nodes,double& cooldown)
{
    if (isCircleClicked(n->x, n->y, n->r) and cooldown < slGetTime())
    {   
        if (n->next == nullptr)
        {
            if (Node* sup = isOverlapingNode(n, nodes); sup != nullptr)
            {
                n->next = sup;
                n->x = sup->x;
                n->y = sup->y;
            }
            else
            {
                Node* nou = new Node;
                nou->floating = true;
                nou->r = n->r;
                nodes.emplace_back(nou);
                n->next = nou;
            }
            if( n->host == nullptr)
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