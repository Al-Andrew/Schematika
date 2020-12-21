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

    fout << "NODES\n ";
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
    fout << "BLOCKS\n ";
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

void openFile(std::vector<Block>& blocks, std::vector<Node*> nodes, unsigned int& nodeIdCount)
{   
    warn("Please open console for input");
    std::string fileName;
    std::string part;
    unsigned int i;
    std::vector<std::string> parts;
    Begin:
        std::cout << "Please input a name for the file you want to open." << std::endl;
        std::getline(std::cin, fileName);
        char answer;
        std::ifstream fin(fileName.c_str());
        if (!(fin.is_open()))
        {
            std::perror("Error ");
            std::cout<<"Do you want to try again ? < Y | N > "<<std :: endl;
            std::cin >> answer;
            answer = std::toupper(answer);
            if (answer == 'Y')
                goto Begin;
            else exit(1);
        }
    std::cout << fileName << std::endl;
    while (!fin.eof())
    {   
         std::getline(fin, part, ' ');  
         parts.push_back(part);
         std::cout << part << std::endl;
    }
    for ( i = 1; i < parts.size() && parts[i] != "BLOCKS"; i += 4)
    {
            for (auto& n : nodes)
            {
                n->id = stoi(parts[i]);
                std::cout << n->id;
                n->x = stod(parts[i + 1]);
                n->y = stod(parts[i + 2]);
                n->r = NODE_RADIUS;
                n->floating = false;
                n->next->id = stod(parts[i + 3]);
                nodes.push_back(n);
                nodeIdCount = n->id;
            }
    }
    i++;
    for (i; i < parts.size(); i += 6)
    {
        for (auto& bl : blocks)
        {
            bl.type = Type::START;
            bl.x = stod(parts[i + 1]);
            bl.y = stod(parts[i + 2]);
            bl.width = stod(parts[i + 3]);
            bl.height = stod(parts[i + 4]);
            bl.text = parts[i + 5];
            bl.floating = false;
            blocks.push_back(bl);
        }
    }
    std::vector<std::string>().swap(parts);
    fin.close();
}
void deleteBlock(std::vector<Block> &blocks, std::vector<Node*> nodes)
{
    for (unsigned int i = 0; i < blocks.size(); i++)
    {
        if (isRectClicked(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height) && isRectClicked(1030, 30, 50, 50))
        {
            blocks.erase(blocks.begin() + i);
            blocks.shrink_to_fit();
            nodes.erase(nodes.begin() + i);
            nodes.shrink_to_fit();
        }
    }
}
void drawControlBar(double x, double y, double width, double height)
{   
    Color c;
    double X = x + width / 2;
    double Y = y + height / 2;
    if (isMouseInRect(X - CLOSE_BUTTON_WIDTH/2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))
    {
        c = BLOCK_DECIZIE_NU_COLOR;
        slSetFontSize(TEXT_MENU_SIZE);
        setForeColor(MENU_TEXT_COLOR);
        slText(X - CLOSE_BUTTON_WIDTH / 2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT - TITLE_UP_SPACE - MENU_BORDER_WIDTH - MENU_BORDER_WIDTH, "Close");
    }
    else c = MENU_BACKGROUND_COLOR;
    drawBorderedRect(c, MENU_BORDER_COLOR, X - CLOSE_BUTTON_WIDTH / 2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT, MENU_BORDER_WIDTH);
    setForeColor(MENU_BORDER_COLOR);
    for (int i = -1; i < 2; i++)
    {
        slLine(X - CLOSE_BUTTON_WIDTH + MENU_BORDER_WIDTH+i, Y - MENU_BORDER_WIDTH, X+i, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT + MENU_BORDER_WIDTH);
        slLine(X - CLOSE_BUTTON_WIDTH + MENU_BORDER_WIDTH+i, Y - SELECT_MENU_HEIGHT + MENU_BORDER_WIDTH, X+i, Y);
    }
}