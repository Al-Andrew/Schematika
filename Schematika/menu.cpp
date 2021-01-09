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

void drawBlocksMenu(const BlockMenu& m, std::vector<Block> blocks)
{
    drawBorderedRect(MENU_BACKGROUND_COLOR, MENU_BORDER_COLOR, m.x, m.y, m.width, m.height, MENU_BORDER_WIDTH);
    slSetFontSize(TEXT_MENU_SIZE);
    slText(m.x, static_cast<double>(WINDOW_HEIGHT)-BLOCK_TITLE_HEIGHT-TITLE_UP_SPACE, "Blocks");
    for (Block bl : m.displayBlocks)
    {
        draw(bl,blocks);
    }
}

Type updateBlockMenu(const BlockMenu& m, const updatedMenu& u, double& cooldown)
{
    double cpy = cooldown;
    for (Block bl : m.displayBlocks)
    {
        update(bl, cooldown);
        if (cpy != cooldown && u.onTop==false)
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

menuButtons updateMenu(Menu& m, updatedMenu& u, double& cooldown)
{
    for (auto b : m.buttons)
    {
        if (updateButton(b, u, cooldown))
            return b.type;
    }
    return menuButtons::NOT_A_BUTTON;
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
    setForeColor(MENU_TEXT_COLOR);
    slText(m.x, m.y-TITLE_UP_SPACE, m.name.c_str());
}

bool updateButton(Button b,  updatedMenu& u, double cooldown)
{
    if (isRectClicked(b.x, b.y, b.width, b.height) and cooldown <= slGetTime())
    {   
        if (b.name == "Code" || b.name == "Help" || b.name == "About")
        {
            u.onTop = true;
        }
        setCooldown(cooldown);
        return true;
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
updatedMenu makeCode()
{
    updatedMenu a;
    a.type = menuButtons::Code;
    a.x = static_cast<double>(WINDOW_WIDTH) - CODE_WIDTH / 2;
    a.y = WINDOW_HEIGHT / 2.f;
    a.width = CODE_WIDTH;
    a.height = CODE_HEIGHT;
    return a;
}
void drawCode(const updatedMenu& a)
{
    drawWindow( a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slSetFontSize(TEXT_MENU_SIZE);
    slSetTextAlign(SL_ALIGN_CENTER);
    slText(a.x, a.y + a.height / 2 - BLOCK_TITLE_HEIGHT - TITLE_UP_SPACE, "Code - Visual Studio");
}
updatedMenu makeHelp()
{
    updatedMenu a;
    a.type = menuButtons::Help;
    a.x = static_cast<double>(WINDOW_WIDTH)-HELP_WIDTH/2;
    a.y = WINDOW_HEIGHT/2.f;
    a.width = HELP_WIDTH;
    a.height = HELP_HEIGHT;
    double posY = SELECT_QUESTION_SPACER/4;
    for (auto& u : allQuestions )
    {
        a.questions.push_back(makeQuestion(posY, u));
        posY += SELECT_QUESTION_SPACER;
    }
    return a;
}
void drawHelp(const updatedMenu& a)
{
    drawWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slSetFontSize(TEXT_MENU_SIZE);
    slSetTextAlign(SL_ALIGN_CENTER);
    slText(a.x, a.y + a.height / 2 - BLOCK_TITLE_HEIGHT - TITLE_UP_SPACE, "Help");
    slSetFontSize(TEXT_SUBMENU_SIZE);
    slText(a.x, a.y + a.height / 2 - SELECT_MENU_HEIGHT - SELECT_MENU_HEIGHT, "Frequently Asked Questions (FAQ): ");
    for (auto& u : a.questions)
    {
        drawQuestion(u);
    }
    slSetTextAlign(SL_ALIGN_CENTER);
    setForeColor(MENU_TEXT_COLOR);
    double Y = a.questions.back().y - 1.5 * SELECT_MENU_HEIGHT;
    slText(a.x, Y, "Tips and Tricks:");
    slSetTextAlign(SL_ALIGN_LEFT);
    slText(a.x - a.width / 2.0 + 2.0*MENU_BORDER_WIDTH, Y - SELECT_SUBMENU_TEXT_SPACER*1.5, "1.  Don't close the console. If the console will be");
    slText(a.x - a.width / 2.0 + 2.0 * MENU_BORDER_WIDTH, Y - SELECT_SUBMENU_TEXT_SPACER * 2.5, "closed, automatically Schematika App will close.");
    slText(a.x - a.width / 2.0 + 2.0 * MENU_BORDER_WIDTH, Y - SELECT_SUBMENU_TEXT_SPACER * 3.5, "2.  A project must have only one START block. ");
    slText(a.x - a.width / 2.0 + 2.0 * MENU_BORDER_WIDTH, Y - SELECT_SUBMENU_TEXT_SPACER * 4.5, "3.  It is possible to write only on the INPUT, ");
    slText(a.x - a.width / 2.0 + 2.0 * MENU_BORDER_WIDTH, Y - SELECT_SUBMENU_TEXT_SPACER * 5.5, "OUTPUT, DECIZIE or CALCUL block.");
    slCircleFill(a.x, 75, 35, 30);
    slSetFontSize(50);
    slSetTextAlign(SL_ALIGN_CENTER);
    setForeColor(MENU_BACKGROUND_COLOR);
    slText(a.x, 57, "?");
}
updatedMenu makeAbout()
{
    updatedMenu a;
    a.type=menuButtons::About;
    a.x = static_cast<double>(WINDOW_WIDTH) - ABOUT_WIDTH / 2;
    a.y = WINDOW_HEIGHT / 2.f;
    a.width = ABOUT_WIDTH;
    a.height = ABOUT_HEIGHT;
    return a;
}
void drawAbout(const updatedMenu &a)
{
    drawWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slSetFontSize(TEXT_MENU_SIZE);
    slSetTextAlign(SL_ALIGN_CENTER);
    slText(a.x, a.y + a.height / 2 - BLOCK_TITLE_HEIGHT - TITLE_UP_SPACE, "About");
    slSetFontSize(35);
    slText(a.x, a.y + a.height / 3, "Schematika");
    slSetFontSize(TEXT_SUBMENU_SIZE);
    slText(a.x, a.y - 130, "Schematika 2021");
    slText(a.x, a.y - 160, "Version 0.6969 (ClosedBeta)");
    slCircleOutline(a.x - 100, a.y - 185, 10, 20);
    slText(a.x -100, a.y -190 , "c");
    slText(a.x, a.y -190,"2021 Aldea Andrei");
    slText(a.x,a.y-220,"Lapteacru Cristian");
}

updatedMenu makeUpdatedMenu(menuButtons u)
{
    switch (u)
    {
    case menuButtons::Code: return makeCode();
    case menuButtons::Help: return makeHelp(); 
    case menuButtons::About: return makeAbout(); 
    default: break;
    }
    return makeHelp();
}
void drawUpdatedMenu(const updatedMenu a)
{
    switch (a.type)
    {
    case menuButtons::Code:
        drawCode(a);
        break;
    case menuButtons::About:
        drawAbout(a);
        break;
    case menuButtons::Help:
        drawHelp(a);
        break;
    default:
        break;
    }
}
std::string questionTypeToString(helpQuestion u)
{   
    switch (u)
    {
    case helpQuestion::Q1: return "1. How to spawn and move a block ?";
    case helpQuestion::Q2: return "2. How to connect the blocks ?";
    case helpQuestion::Q3: return "3. How to delete a block or to start a new project?";
    case helpQuestion::Q4: return "4. How to write on the blocks ?";
    case helpQuestion::Q5: return "5. How to save and open the project ?";
    case helpQuestion::Q6: return "6. How to run the project ?";
    case helpQuestion::Q7: return "7. How to view the code of the project ?";
    default: return "Err";
    }
    return "Err";
}

Question makeQuestion(double posY, helpQuestion type)
{
    Question b;
    b.name = questionTypeToString(type);
    b.type = type;
    b.width = slGetTextWidth(b.name.c_str());
    b.height = slGetTextHeight(b.name.c_str());
    b.x = static_cast<double>(WINDOW_WIDTH) - HELP_WIDTH + 2.0* MENU_BORDER_WIDTH;
    b.y = HELP_HEIGHT - SELECT_MENU_HEIGHT* 3.0 - posY;
    return b;
}

void drawQuestion(const Question m)
{
    Color text;
    if (isMouseInRect(m.x + m.width/1.5, m.y, m.width + m.width/4, m.height))
        text = MENU_TEXT_HOVER_COLOR;
    else
        text = MENU_TEXT_COLOR;
    slSetFontSize(TEXT_SUBMENU_SIZE);
    setForeColor(text);
    slSetTextAlign(SL_ALIGN_LEFT);
    slText(m.x, m.y, m.name.c_str());
}
updatedSubMenu makeQuestion(helpQuestion u)
{
    updatedSubMenu a;
    a.type = u;
    a.x = static_cast<double>(WINDOW_WIDTH) - HELP_WIDTH / 2;
    a.height = HELP_HEIGHT / 1.0 - SELECT_MENU_HEIGHT + MENU_BORDER_WIDTH;
    a.y = a.height/2.0;
    a.width = HELP_WIDTH;
    return a;
}

void drawQ1(const updatedSubMenu &a)
{
    drawSubMenuWindow(a.x,a.y,a.width,a.height);
    setForeColor(MENU_TEXT_COLOR);
    double y = a.y + a.height / 3;
    slText(a.x - a.width/2 + BACK_BUTTON_WIDTH + 10, a.y + a.height/2 - SELECT_MENU_HEIGHT/1.5, "How to spawn and move a block ?");
    slText(a.x - a.width/6, y, "1.   In order to spawn a block, it is ");
    slText(a.x - a.width / 6, y - SELECT_SUBMENU_TEXT_SPACER, "necessary to left click on the wanted ");
    slText(a.x - a.width / 6, y - SELECT_SUBMENU_TEXT_SPACER * 2.0, "block from the block-menu, that is ");
    slText(a.x - a.width / 6, y - SELECT_SUBMENU_TEXT_SPACER * 3.0, "located on the right side of the window.");
    slText(a.x - a.width / 6, y - SELECT_SUBMENU_TEXT_SPACER * 4.0, "( like in the image nr. 1 )");
    slText(a.x - a.width / 2.3, y - SELECT_SUBMENU_TEXT_SPACER * 7.0, "2.  In order to move a spawned block, it is necessary to ");
    slText(a.x - a.width / 2.3, y - SELECT_SUBMENU_TEXT_SPACER * 8.0, "left click on the block, and now the block will follow ");
    slText(a.x - a.width / 2.3, y - SELECT_SUBMENU_TEXT_SPACER * 9.0, "mouse. If you want to paste the block, you just have to ");
    slText(a.x - a.width / 2.3, y - SELECT_SUBMENU_TEXT_SPACER * 10.0, "left click. ( like in the image nr. 2 )");
}

void drawQ2(const updatedSubMenu& a)
{
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to connect the blocks ?");
    slSetTextAlign(SL_ALIGN_LEFT);
    slText(a.x - a.width/5, a.y+a.height/2.5, "   In order to connect two blocks, it is ");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER, "necessary to follow the steps below :");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER *2.0, "1.    Firstly, you have to right click on");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 3.0, "the connector (the circle) of the block, ");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 4.0, "that you want to connect.");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 5.5, "2.    Now, the connection (the line) is ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 6.5, "following your mouse. And in order to ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 7.5, "connect the blocks, is is necessary to");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 8.5, "move the connetion above the wanted ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 9.5, "connector and to right click one more time.");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 11.0, "3.   Now the blocks are connected, and ");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 12.0, "and of course after the connection you can");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 13.0, "move the blocks and the connection will");
    slText(a.x - a.width / 5, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 14.0, "follow the moving block.");

}
void drawQ3(const updatedSubMenu& a)
{
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to delete a block or how to start a new project ?");
    slText(a.x - a.width / 2.3, a.y + a.height / 10, "1.  In order to delete a block, it is necessary to left click");
    slText(a.x - a.width / 2.3, a.y + a.height / 10 - SELECT_SUBMENU_TEXT_SPACER, "on the block and to move it above the trash, where you ");
    slText(a.x - a.width / 2.3, a.y + a.height / 10 - 2.0 * SELECT_SUBMENU_TEXT_SPACER, "have to left click one more time. (like in the image nr. 1 )");
    slText(a.x - a.width / 2.3, a.y - a.height / 4, "2.  In order to start a new project, it is necessary to click");
    slText(a.x - a.width / 2.3, a.y - a.height / 4 - SELECT_SUBMENU_TEXT_SPACER, "on the New button. ( like in the image nr. 2 )");
    slText(a.x - a.width / 2.3, a.y - a.height / 4 - 2.0*SELECT_SUBMENU_TEXT_SPACER,"Remember: By pressing the New button, all your previous ");
    slText(a.x - a.width / 2.3, a.y - a.height / 4 - 3.0 * SELECT_SUBMENU_TEXT_SPACER, "unsaved actions will be automatically deleted.");
}

void drawQ4(const updatedSubMenu& a)
{
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to write on the blocks ?");
    slText(a.x -a.width/10 , a.y + a.height / 2.6, " 1.   First of all, you are able to write");
    slText(a.x-a.width/10, a.y+a.height/2.6 - SELECT_SUBMENU_TEXT_SPACER," only on below enumerated blocks:");
    slText(a.x - a.width / 10, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER*2.0, " - Input Block   - Output Block");
    slText(a.x - a.width / 10, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER*3.0, " - Calcul Block  - Decizie Block");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER*5.0, "2.  In order to write on the blocks, it is necessary to left ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER *6.0, "click on the block and after this to press enter button. And");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 7.0, "in the lower left corner will appear this message: Please");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 8.0, "open console for input.");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 12.0, "3.    Now it is necessary to open the console and there to  ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 13.0, " write the text, that you want your block to contain.");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 14.0, "After this, you should press enter button and to reopen ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 15.0, "Schematika App. ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 16.0, "Remember: Don't close the console. In case you close the ");
    slText(a.x - a.width / 2.2, a.y + a.height / 2.6 - SELECT_SUBMENU_TEXT_SPACER * 17.0, "console, the Schematika App will close.");
}

void drawQ5(const updatedSubMenu& a)
{   
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to save and open the project ?");
    slText(a.x + a.width / 6, a.y + a.height / 2.4, "1.   In order to save");
    slText(a.x + a.width / 6, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER*0.8, "the project, it is");
    slText(a.x - a.width / 2.1, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER * 1.8, "necessary to click on the Save button.In the lower left corner");
    slText(a.x - a.width / 2.1, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER * 2.8, "will appear the message: Please open console for input.");
    slText(a.x - a.width / 2.1, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER * 6.0, "Now it is necessary to open the console and there to write");
    slText(a.x - a.width / 2.1, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER * 7.0, "the name of your project ( example.txt ). By pressing enter,");
    slText(a.x - a.width / 2.1, a.y + a.height / 2.4 - SELECT_SUBMENU_TEXT_SPACER * 8.0, "your project will be saved with the given name.");
    slText(a.x + a.width / 6, a.y - 22 , "2.   In order to open");
    slText(a.x + a.width / 6, a.y - 22 - SELECT_SUBMENU_TEXT_SPACER*0.8, "a project, it is ");
    slText(a.x - a.width / 2.1, a.y -22 -  SELECT_SUBMENU_TEXT_SPACER * 1.8, "necessary to click on the Open button. In the lower left");
    slText(a.x - a.width / 2.1, a.y -22 - SELECT_SUBMENU_TEXT_SPACER * 2.8, "corner will appear the message: Please open console for");
    slText(a.x - a.width / 2.1, a.y - 22 - SELECT_SUBMENU_TEXT_SPACER * 3.8, "input.");
    slText(a.x - a.width / 2.1, a.y -22 - SELECT_SUBMENU_TEXT_SPACER * 6.5, "   Now it is necessary to open the console and there to write");
    slText(a.x - a.width / 2.1, a.y -22 - SELECT_SUBMENU_TEXT_SPACER * 7.5, "the name of your project ( example.txt ). By pressing enter,");
    slText(a.x - a.width / 2.1, a.y -22 - SELECT_SUBMENU_TEXT_SPACER * 8.5, "if exists a project with the given name, then it will open.");
}
void drawQ6(const updatedSubMenu& a)
{
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to run the project ?");
    slText(a.x - a.width/6.3, a.y + a.height / 2.5, "1.    First of all, in order to be able to run");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 -SELECT_SUBMENU_TEXT_SPACER, "the project, it is necessary to have some");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER*2.0, "spawned, connected blocks. Also,");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 3.0, "INPUT, OUTPUT, DECIZIE and CALCUL");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 4.0, " blocks must contain an input.");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 5.0, "Remember, use only the variables");
    slText(a.x - a.width / 6.3, a.y + a.height / 2.5 - SELECT_SUBMENU_TEXT_SPACER * 6.0, "from INPUT block / blocks.");
    slText(a.x - a.width / 2.1, a.y + 20, "2.    In order to run");
    slText(a.x - a.width / 2.1, a.y + 20 - SELECT_SUBMENU_TEXT_SPACER*0.8, "the project, it is ");
    slText(a.x - a.width / 2.1, a.y +20 - SELECT_SUBMENU_TEXT_SPACER * 1.8, "necessary to click on the Run button. In the lower left corner");
    slText(a.x - a.width / 2.1, a.y +20 - SELECT_SUBMENU_TEXT_SPACER * 2.8, " will appear the message: Please open console for input.");
    slText(a.x + a.width / 6.1, a.y - a.height / 5.9, " Now it is necessary");
    slText(a.x + a.width / 6.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER*0.8, "to open the console");
    slText(a.x - a.width / 2.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER * 1.8, "and there to input a value for every given variables from the");
    slText(a.x - a.width / 2.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER * 2.8, "project. Finally, by pressing");
    slText(a.x - a.width / 2.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER * 3.8, "enter key, the project will run");
    slText(a.x - a.width / 2.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER * 4.8, "and in the console will appear");
    slText(a.x - a.width / 2.1, a.y - a.height / 5.9 - SELECT_SUBMENU_TEXT_SPACER * 5.8, "the result of the project.");
}
void drawQ7(const updatedSubMenu& a)
{
    drawSubMenuWindow(a.x, a.y, a.width, a.height);
    setForeColor(MENU_TEXT_COLOR);
    slText(a.x - a.width / 2 + BACK_BUTTON_WIDTH + 10, a.y + a.height / 2 - SELECT_MENU_HEIGHT / 1.5, "How to view the code of your project ?");
}
void drawUpdatedSubMenu(const updatedSubMenu a)
{   
    slSetFontSize(TEXT_MENU_SIZE);
    slSetTextAlign(SL_ALIGN_LEFT);
    setForeColor(MENU_TEXT_COLOR);
    switch (a.type)
    {
    case helpQuestion::Q1: return drawQ1(a);
    case helpQuestion::Q2: return drawQ2(a);
    case helpQuestion::Q3: return drawQ3(a);
    case helpQuestion::Q4: return drawQ4(a);
    case helpQuestion::Q5: return drawQ5(a);
    case helpQuestion::Q6: return drawQ6(a);
    case helpQuestion::Q7: return drawQ7(a);
    default: break;
    }
}
bool updateQuestion(Question b, updatedSubMenu u, double cooldown)
{
    if (isRectClicked(b.x + b.width / 1.5, b.y, b.width + b.width / 4, b.height) and cooldown <= slGetTime())
    {
        setCooldown(cooldown);
        return true;
    }
    return false;
}

helpQuestion updateSubMenu(updatedMenu& m, const updatedSubMenu u, double& cooldown, bool onTop)
{
    for (auto b : m.questions)
    {
        if (updateQuestion(b, u, cooldown)&& m.onTop == true && onTop == false)
            return b.type;
    }
    return helpQuestion::NOT_A_QUESTION;
}