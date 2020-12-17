#include "helpers.hpp"
#include "sl.h"

void setBackColor(const Color& c)
{
    slSetBackColor(c.r / 255.f, c.g / 255.f, c.b / 255.f);
}

void setForeColor(const Color& c)
{
    slSetForeColor(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a);
}

bool isMouseInRect(double x, double y, double width, double height)
{
    double mx = slGetMouseX();
    double my = slGetMouseY();
    return (mx >= x - width / 2.f && mx <= x + width / 2.f) && (my >= y - height / 2.f && my <= y + height / 2.f);
}

bool isMouseInCircle(double x, double y, double r)
{
    double mx = slGetMouseX();
    double my = slGetMouseY();
    double dist = sqrt((mx - x) * (mx - x) + (my - y) * (my - y));
    return dist <= r;
}

bool isCircleInCircle(double x1, double y1, double r1, double x2, double y2, double r2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2);
}

bool isRectClicked(double x, double y, double width, double height)
{
    return slGetMouseButton(SL_MOUSE_BUTTON_LEFT) && isMouseInRect(x, y, width, height);
}

bool isCircleClicked(double x, double y, double r)
{
    return slGetMouseButton(SL_MOUSE_BUTTON_RIGHT) && isMouseInCircle(x, y, r);
}

void limitsOfFloatingBlocks(Block& b)
{
    if (slGetMouseX() < BLOCK_LIMITS_LEFT && slGetMouseY() < BLOCK_LIMITS_DOWN)
    {
        b.x = BLOCK_LIMITS_LEFT;
        b.y = BLOCK_LIMITS_DOWN;
    }
    else if (slGetMouseX() < BLOCK_LIMITS_LEFT && slGetMouseY() > BLOCK_LIMITS_UP)
    {
        b.x = BLOCK_LIMITS_LEFT;
        b.y = BLOCK_LIMITS_UP;
    }
    else if (slGetMouseX() < BLOCK_LIMITS_LEFT)
    {
        b.x = BLOCK_LIMITS_LEFT;
    }
    else if (slGetMouseX() > BLOCK_LIMITS_RIGHT && slGetMouseY() < BLOCK_LIMITS_DOWN)
    {
        b.x = BLOCK_LIMITS_RIGHT;
        b.y = BLOCK_LIMITS_DOWN;
    }
    else if (slGetMouseX() > BLOCK_LIMITS_RIGHT && slGetMouseY() > BLOCK_LIMITS_UP)
    {
        b.x = BLOCK_LIMITS_RIGHT;
        b.y = BLOCK_LIMITS_UP;
    }
    else if (slGetMouseX() > BLOCK_LIMITS_RIGHT)
    {
        b.x = BLOCK_LIMITS_RIGHT;
    }
    else if (slGetMouseY() < BLOCK_LIMITS_DOWN)
    {
        b.y = BLOCK_LIMITS_DOWN;
    }
    else if (slGetMouseY() > BLOCK_LIMITS_UP)
    {
        b.y = BLOCK_LIMITS_UP;
    }
}

void setCooldown(double& cooldown)
{
    cooldown = slGetTime() + ACTION_COOLDOWN;
}

void drawBorderedRect(const Color& fill, const Color& bord, const double x, const double y, const double w, const double h, const double bw)
{
    setForeColor(fill);
    slRectangleFill(x, y, w, h);
    setForeColor(bord);
    slRectangleFill(x - (w / 2.f - bw / 2.f), y, bw, h);
    slRectangleFill(x + (w / 2.f - bw / 2.f), y, bw, h);
    slRectangleFill(x, y - (h / 2.f - bw / 2.f), w, bw);
    slRectangleFill(x, y + (h / 2.f - bw / 2.f), w, bw);
}

Node* isOverlapingNode(const Node* n, const std::vector<Node*>& nodes)
{
    for (Node* nod : nodes)
    {
        if (nod != n && nod->host != nullptr &&isMouseInCircle(nod->x, nod->y, nod->r))
            return nod;
    }
    return nullptr;
}


void warn(std::string message)
{
    setForeColor(CONSOLE_WARNING_COLOR);
    slText(slGetTextWidth(message.c_str()) / 2.f + 10, slGetTextHeight(message.c_str()) / 2.f + 10, message.c_str());
    slRender();
}

std::string typeToString(Type t)
{
    switch (t)
    {
    case Type::START:
        return "START";
    case Type::CALCUL:
        return "CALCUL";
    case Type::DECIZIE:
        return "DECIZIE";
    case Type::INPUT:
        return "INPUT";
    case Type::OUTPUT:
        return "OUTPUT";
    case Type::STOP:
        return "STOP";
    }
    return "NOT_A_BLOCK";
}

void saveToFile(std::vector<Block> blocks, std::vector<Node*> nodes)
{
    warn("Please open console for input");

    std::string fileName;
    std::cout << "Please input a name for the file you want to save." << std::endl;
    std::getline(std::cin,fileName);
    std::cout << "The file is successfully saved"<<std::endl;
    std::ofstream fout(fileName.c_str());

    fout << "NODES\n";
    for (auto nd : nodes)
    {
        fout << nd->id << " "  << nd->x << " "  << nd->y;
        if (nd->next != nullptr)
        {
            fout << " " << nd->next->id;
        }
        else
        {
            fout << " " <<0;
        }
        fout << "\n";
    }
    fout << "BLOCKS\n";
    for (auto bl : blocks)
    {
        fout << typeToString(bl.type) << " " << bl.x << " " << bl.y << " " << bl.width << " " << bl.height << " |" << bl.text << "| ";
        for (auto n : bl.nodes)
        {
            fout << n->id << " ";
        }
        fout << "\n";
    } 

}

std::string openFile()
{   
    warn("Please open console for input");
    std::string fileName;
    Begin:
        std::cout << "Please input a name for the file you want to open." << std::endl;
        std::getline(std::cin, fileName);
        std::string line;
        std::ifstream fin(fileName.c_str());
        if (!(fin.is_open()))
        {
            std::perror("Error ");
            std::cout<<std :: endl;
            goto Begin;
        }
    std::cout << fileName << std::endl;
    while (!fin.eof())
    {   
         getline(fin, line);  
         std::cout << line << std::endl;
    }
    fin.close();
    return line;
}
void deleteBlock(std::vector<Block> &blocks)
{
    for (unsigned int i = 0; i < blocks.size(); i++)
    {
        if (isRectClicked(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height) && isRectClicked(1030, 30, 50, 50))
        {
            blocks.erase(blocks.begin() + i);
        }
    }
}