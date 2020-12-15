#include "blocks.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include "menu.hpp"
#include "sl.h"

BlockMenu makeBlockMenu()
{
    BlockMenu b;
    b.x = static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH / 2.f;
    b.y = static_cast<double>(WINDOW_HEIGHT) / 2.f;
    b.width = SELECT_BLOCK_MENU_WIDTH;
    b.height = SELECT_BLOCK_MENU_HEIGHT;
    double y = static_cast<double>(WINDOW_HEIGHT) - SELECT_BLOCK_MENU_SPACER / 2.f;
    for (auto t : allTypes)
    {
        b.displayBlocks.push_back(generate(t));
        double oldX = b.displayBlocks.back().x;
        double oldY = b.displayBlocks.back().y;
        b.displayBlocks.back().x = b.x;
        b.displayBlocks.back().y = y - BLOCK_TITLE_HEIGHT;
        double dx = b.x - oldX;
        double dy = y - oldY-BLOCK_TITLE_HEIGHT;
        for (Node*& n : b.displayBlocks.back().nodes)
        {
            n->x += dx;
            n->y += dy;
        }
        y -= SELECT_BLOCK_MENU_SPACER;
    }
    

    return b;
}
Menu makeMenu()
{
    Menu b;
    b.x=  (WINDOW_WIDTH - SELECT_BLOCK_MENU_WIDTH)/2.f;
    b.y = static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2.f;
    b.width = static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH;
    b.height = SELECT_MENU_HEIGHT;
    std::vector<std::string> ButtonNames = { "File","Project","Undo","Help"};
    double positionX= MENU_BORDER_WIDTH;
    for (unsigned int i = 0; i < ButtonNames.size(); i++)
    {
         std::string name = ButtonNames[i];
         double width = slGetTextWidth(name.c_str())+MENU_BORDER_WIDTH;
         double height = SELECT_MENU_HEIGHT;
         double x = positionX + width/2.f - (MENU_BORDER_WIDTH);
         double y = WINDOW_HEIGHT - height/2;
         positionX += width-MENU_BORDER_WIDTH;
         b.buttons.push_back(makeButton(name, width, height, x, y));
    }
  
    return b;
}
void drawMenu(const BlockMenu& m, const Menu& n )
{
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, m.x, m.y, m.width, m.height, MENU_BORDER_WIDTH);
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, n.x, n.y, n.width, n.height, MENU_BORDER_WIDTH);
    slSetFontSize(TEXT_MENU_SIZE);
    slText(m.x, static_cast<double>(WINDOW_HEIGHT)-BLOCK_TITLE_HEIGHT-TITLE_UP_SPACE, "Blocks");
    for (Block bl : m.displayBlocks)
    {
        draw(bl);
    }
    for (Button button : n.buttons)
    {
        drawButton(button);
    }
}

Type updateMenu(const BlockMenu& m, double& cooldown)
{
    double cpy = cooldown;
    for (Block bl : m.displayBlocks)
    {
        update(bl,cooldown);
        if (cpy != cooldown)
            return bl.type;
    }
    return Type::NOT_A_BLOCK;
}
Button makeButton(std::string name, double width, double height, double x, double y)
{
    Button b;
    b.name = name;
    b.width = width;
    b.height = height;
    b.x = x;
    b.y = y;
    return b;
}
void drawButton(const Button& m)
{
    Color background;
    if (isMouseInRect(m.x, m.y, m.width, m.height))
        background = MENU_HOVER_COLOR;
    else
        background = MENU_BACKGROUND_COLOR;
    drawBorderedRect(background,MENU_BORDER_COLOR, m.x, m.y, m.width, m.height, MENU_BORDER_WIDTH);
    slSetFontSize(TEXT_MENU_SIZE);
    slText(m.x, m.y-TITLE_UP_SPACE, m.name.c_str());
}