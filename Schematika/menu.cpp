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

void drawBlocksMenu(const BlockMenu& m)
{
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, m.x, m.y, m.width, m.height, MENU_BORDER_WIDTH);
    slSetFontSize(TEXT_MENU_SIZE);
    slText(m.x, static_cast<double>(WINDOW_HEIGHT)-BLOCK_TITLE_HEIGHT-TITLE_UP_SPACE, "Blocks");
    for (Block bl : m.displayBlocks)
    {
        draw(bl);
    }
}

Type updateBlockMenu(const BlockMenu& m, double& cooldown)
{
    double cpy = cooldown;
    for (Block bl : m.displayBlocks)
    {
        update(bl, cooldown);
        if (cpy != cooldown)
            return bl.type;
    }
    return Type::NOT_A_BLOCK;
}

Menu makeMenu()
{
    Menu b;
    b.x=  (WINDOW_WIDTH - SELECT_BLOCK_MENU_WIDTH)/2.f;
    b.y = static_cast<double>(WINDOW_HEIGHT) - SELECT_MENU_HEIGHT / 2.f;
    b.width = static_cast<double>(WINDOW_WIDTH) - SELECT_BLOCK_MENU_WIDTH;
    b.height = SELECT_MENU_HEIGHT;


    double positionX = MENU_BORDER_WIDTH;
    for (auto t : allMenuButtons)
    {
         b.buttons.push_back(makeButton(positionX, t));
         positionX += b.buttons.back().width-MENU_BORDER_WIDTH;
    }
  
    return b;
}

void drawMenu(const Menu &m)
{
    drawBorderedRect(MENU_BACKGROUND_COLOR,MENU_BORDER_COLOR, m.x,m.y,m.width,m.height, MENU_BORDER_WIDTH);
    for (auto& b : m.buttons)
    {
        drawButton(b);
    }
}

menuButtons updateMenu(Menu& m, double& cooldown)
{
    return menuButtons::New;//To do
}

Button makeButton(double posX, menuButtons type)
{
    Button b;
    b.name = buttonTypeToString(type);
    b.type = type;
    b.width = slGetTextWidth(b.name.c_str()) + MENU_BORDER_WIDTH;;
    b.height = SELECT_MENU_HEIGHT;;
    b.x = posX + b.width/2.f - (MENU_BORDER_WIDTH);
    b.y = WINDOW_HEIGHT - b.height / 2;
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

bool updateButton(Button b, double cooldown)
{
    if (isRectClicked(b.x, b.y, b.width, b.height) and cooldown <= slGetTime())
    {
        return true;
        setCooldown(cooldown);
    }
    return false;
}


std::string buttonTypeToString(menuButtons type)
{
    switch (type)
    {
        case menuButtons::New: return "New";
        case menuButtons::Save: return "Save";
        case menuButtons::Open: return "Open";
        case menuButtons::Run: return "Run";
        case menuButtons::Code: return "Code";
        case menuButtons::Help: return "Help";
        case menuButtons::About: return "About";
        default: return "Err";
    }
        return "Err";
}