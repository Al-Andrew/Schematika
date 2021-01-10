#include "helpers.hpp"
#include "sl.h"
#include <stack>

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
    double BLOCK_LIMITS_LEFT = b.width / 2 + 15;
    double BLOCK_LIMITS_RIGHT = WINDOW_WIDTH / 1.0 - SELECT_BLOCK_MENU_WIDTH - MENU_BORDER_WIDTH *2.7 - b.width / 2 ;
    double BLOCK_LIMITS_DOWN = b.height / 2 + 15;
    double BLOCK_LIMITS_UP = WINDOW_HEIGHT/1.0 - SELECT_MENU_HEIGHT - MENU_BORDER_WIDTH / 2 - b.height / 2 - 14;
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


Type stringToType(std::string t)
{
    if (t == "START")
        return Type::START;
    if (t == "STOP")
        return Type::STOP;
    if (t == "INPUT")
        return Type::INPUT;
    if (t == "OUTPUT")
        return Type::OUTPUT;
    if (t == "DECIZIE")
        return Type::DECIZIE;
    if (t == "CALCUL")
        return Type::CALCUL;
    return Type::NOT_A_BLOCK;
}


void saveToFile(std::vector<Block> blocks, std::vector<Node*> nodes, std::string fileName)
{
    warn("Please open console for input");

    if (fileName == "")
    {
        std::cout << "Please input a name for the file you want to save." << std::endl;
        std::getline(std::cin,fileName);
    }
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
        fout << typeToString(bl.type) << " " << bl.x << " " << bl.y << " " << bl.width << " " << bl.height << " $ " << bl.text << " $ ";
        for (auto n : bl.nodes)
        {
            fout << n->id << " ";
        }
        fout << "\n";
    } 
    if(fileName != "")
    std::cout << "The file is successfully saved"<<std::endl;
}

void openFile(std::vector<Block>& blocks, std::vector<Node*>& nodes, std::string fileName)
{   
    warn("Please open console for input");
    if (fileName == "")
    {
        std::cout << "Please input a name for the file you want to open." << std::endl;
        std::getline(std::cin, fileName);
    }
    std::ifstream fin(fileName);
    std::string line;
    std::getline(fin, line); // load the NODES token;
    blocks.clear();
    blocks.reserve(100);
    nodes.clear();
    nodes.reserve(150);

    std::vector<int> pairs;

    while (std::getline(fin, line, '\n') && line != "BLOCKS") // Get a line until BLOCKS section
    {
        std::vector<std::string> tokens;
        std::stringstream l(line);
        
        for (std::string tok; std::getline(l, tok, ' '); tokens.emplace_back(tok)); //Split the line into tokens

        Node *n = new Node;
        n->id = std::stoi(tokens[0]);
        n->x = std::stod(tokens[1]);
        n->y = std::stod(tokens[2]);
        n->r = NODE_RADIUS;
        n->floating = false;
        pairs.push_back(std::stoi(tokens[3])-1);
        nodes.push_back(n);
    }//Done reading in the nodes;
    for (int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i] != -1)
            nodes[i]->next = nodes[pairs[i]]; // Set appropriate nexts
        else
            nodes[i]->next = nullptr;
    }
    while (std::getline(fin, line, '\n'))//Now read till the end of the file for blocks
    {
        std::vector<std::string> tokens;
        std::stringstream l(line);

        for (std::string tok; std::getline(l, tok, ' '); tokens.emplace_back(tok)); //Split the line into tokens
        
        Block b;
        b.type = stringToType(tokens[0]);
        b.x = std::stod(tokens[1]);
        b.y = std::stod(tokens[2]);
        b.width = std::stod(tokens[3]);
        b.height = std::stod(tokens[4]);
        b.floating = false;

        std::string text;
        unsigned int i = 5;
        i++;
        while (tokens[i] != "$")
        {
            text += tokens[i++] + (((b.type == Type::CALCUL || b.type == Type::DECIZIE || b.type == Type::OUTPUT) && tokens[i] != "$")?" ":"");
        }
        i++;
        b.text = text == "  "?"":text;
        b.nodes.clear();
        while (i < tokens.size())
        {
            b.nodes.push_back(nodes[std::stoi(tokens[i])-1]);
            b.nodes.back()->host = &b;
            i++;
        }
        blocks.push_back(b);
        for (auto n : blocks.back().nodes)
            n->host = &blocks.back();        
    }

}
void deleteBlock(std::vector<Block> &blocks, std::vector<Node*>& nodes)
{
    for (unsigned int i = 0; i < blocks.size(); i++)
    {
        if (isRectClicked(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height) && isRectClicked(static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH - SELECT_TRASH_WIDTH, SELECT_TRASH_HEIGHT / 1.3, SELECT_TRASH_WIDTH +10, SELECT_TRASH_HEIGHT+10))
        {
            for ( int j = 0; j < nodes.size(); j++)
            {
               if ((nodes[j]->x == blocks[i].x || nodes[j]->x == blocks[i].x - blocks[i].width / 2 || nodes[j]->x == blocks[i].x + blocks[i].width / 2)&& (nodes[j]->y == blocks[i].y - blocks[i].height/2 || nodes[j]->y == blocks[i].y + blocks[i].height / 2))
                {
                    nodes.erase(nodes.begin() + j);
                    j--;
                }
                else if (nodes[j]->next != nullptr)
                    if ((nodes[j]->next->x == blocks[i].x || nodes[j]->next->x == blocks[i].x - blocks[i].width / 2 || nodes[j]->next->x == blocks[i].x + blocks[i].width / 2) && (nodes[j]->next->y == blocks[i].y - blocks[i].height / 2 || nodes[j]->next->y == blocks[i].y + blocks[i].height / 2))
                        nodes[j]->next = nullptr;
            }       
            blocks.erase(blocks.begin() + i);
        }
    }
    int i = 1;
    for (auto n : nodes)
    {
        n->id = i++;
    }
}
void drawWindow(double x, double y, double width, double height)
{   
    Color c;
    double X = x + width / 2;
    double Y = y + height / 2;
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, x, y, width, height, MENU_BORDER_WIDTH);
    if (isMouseInRect(X - CLOSE_BUTTON_WIDTH / 2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT))
    {
        c = BLOCK_DECIZIE_NU_COLOR;
        slSetFontSize(TEXT_MENU_SIZE);
        setForeColor(MENU_TEXT_COLOR);
        slSetTextAlign(SL_ALIGN_CENTER);
        slText(X - CLOSE_BUTTON_WIDTH / 2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT - TITLE_UP_SPACE - MENU_BORDER_WIDTH - MENU_BORDER_WIDTH, "Close");
    }
    else c = MENU_BACKGROUND_COLOR;
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, x, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2, width, SELECT_MENU_HEIGHT, MENU_BORDER_WIDTH);
    drawBorderedRect(c, MENU_BORDER_COLOR, X - CLOSE_BUTTON_WIDTH / 2, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2, CLOSE_BUTTON_WIDTH, SELECT_MENU_HEIGHT, MENU_BORDER_WIDTH);
    setForeColor(MENU_BORDER_COLOR);
    for (int i = -1; i < 2; i++)
    {
        slLine(X - CLOSE_BUTTON_WIDTH + MENU_BORDER_WIDTH+i, Y - MENU_BORDER_WIDTH, X+i, static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT + MENU_BORDER_WIDTH);
        slLine(X - CLOSE_BUTTON_WIDTH + MENU_BORDER_WIDTH+i, Y - SELECT_MENU_HEIGHT + MENU_BORDER_WIDTH, X+i, Y);
    }
}
void drawSubMenuWindow(double x, double y, double width, double height)
{
    Color c, arrow;
    double X = x - width / 2;
    double Y = y + height / 2;
    if (isMouseInRect(X + BACK_BUTTON_WIDTH / 2, Y - SELECT_MENU_HEIGHT / 2, BACK_BUTTON_WIDTH, SELECT_MENU_HEIGHT))
    {
        c = BACK_HOVER_COLOR;
        arrow = MENU_BACKGROUND_COLOR;
    }
    else
    {
        c = MENU_BACKGROUND_COLOR;
        arrow = BACK_HOVER_COLOR;
    }
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, x, y, width, height, MENU_BORDER_WIDTH);
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, x, Y - SELECT_MENU_HEIGHT / 2, width, SELECT_MENU_HEIGHT, MENU_BORDER_WIDTH);
    drawBorderedRect(c, MENU_BORDER_COLOR, X + BACK_BUTTON_WIDTH / 2,Y - SELECT_MENU_HEIGHT/2, BACK_BUTTON_WIDTH, SELECT_MENU_HEIGHT, MENU_BORDER_WIDTH);
    setForeColor(arrow);
    for (int i = -1; i < 2; i++)
    {
        slLine(X + BACK_BUTTON_WIDTH / 4, Y - SELECT_MENU_HEIGHT/2 + i, X + BACK_BUTTON_WIDTH / 4.0 * 3, Y - SELECT_MENU_HEIGHT/2 + i);
   
    }
    for (int i = 0; i < 10; i++)
    {
        slLine(X + BACK_BUTTON_WIDTH / 4.7 + i, Y - SELECT_MENU_HEIGHT / 2 + i, X + BACK_BUTTON_WIDTH / 4.7 + i, Y - SELECT_MENU_HEIGHT / 2 - i);
    }
    
}

void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}


bool stack_find(std::stack<Block*> st, Block* el)
{
    while (st.empty() == false)
    {
        if (st.top() == el)
            return true;
        st.pop();
    }
    return false;
}