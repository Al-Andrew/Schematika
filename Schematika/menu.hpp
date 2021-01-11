#pragma once
#include "sl.h"
#include "string"
#include "helpers.hpp"
#include "blocks.hpp"
#include <array>

enum class menuButtons
{
    New,
    Save,
    Open,
    Run,
    Code,
    Help,
    About,
    NOT_A_BUTTON
};

enum class helpQuestion
{
    Q1,
    Q2,
    Q3,
    Q4,
    Q5,
    Q6,
    Q7,
    NOT_A_QUESTION
};

const std::vector<helpQuestion> allQuestions = { helpQuestion::Q1, helpQuestion::Q2, helpQuestion::Q3, helpQuestion::Q4, helpQuestion::Q5,  helpQuestion::Q6, helpQuestion::Q7 };

const std::vector<menuButtons> allMenuButtons = { menuButtons::New, menuButtons::Save, menuButtons::Open, menuButtons::Run,menuButtons::Code,menuButtons::Help,menuButtons::About };

/// <summary>
/// Struct to hold the data for the Block menu
/// </summary>
/// <author>Andrei</author>
struct BlockMenu
{
    std::string name;
    double x = 0, y = 0;
    double width = 0, height = 0;
    std::vector<Block> displayBlocks;
    bool isClicked = false;
};
/// <summary>
/// Struct to hold the data for the bottons of the menu
/// </summary>
/// <author>Cristi and Andrei</author>
struct Button
{
    std::string name;
    menuButtons type = menuButtons::New;
    double width = 0, height = 0;
    double x = 0, y = 0;
};

struct Question
{
    std::string name;
    helpQuestion type = helpQuestion::Q1;
    double width = 0, height = 0;
    double x = 0, y = 0;
};

/// <summary>
/// Struct to hold the data for the  menu
/// </summary>
/// <author>Cristi</author>
struct Menu
{
    double x = 0, y = 0;
    double width = 0, height = 0;
    std::vector<Button> buttons;
};

/// <summary>
/// Struct to hold the data for the  menu windows 
/// </summary>
/// <author>Cristi</author>
struct updatedMenu
{   
    menuButtons type = menuButtons::Code;
    double x = 0, y = 0;
    double width = 0, height = 0;
    bool onTop = false; //for Menu windows (prevents the clicking under the window)
    std::vector<Question> questions;
};

/// <summary>
/// Struct to hold the data for the  submenu windows
/// </summary>
/// <author>Cristi</author>
struct updatedSubMenu
{
    helpQuestion type = helpQuestion::Q1;
    double x = 0, y = 0;
    double width = 0, height = 0;
};

/// <summary>
/// Pseudo-constructor for the Block menu
/// </summary>
/// <returns>The Block menu(should be singleton)</returns>
/// <author>Andrei</author>
BlockMenu makeBlockMenu();

/// <summary>
/// Pseudo-constructor for the  menu
/// </summary>
/// <returns>The menu(should be singleton)</returns>
/// <author>Cristi and Andrei</author>
Menu makeMenu();

/// <summary>
/// Draws the Blocks menu
/// </summary>
/// <param name="m">The Blocks menu struct</param>
/// <author>Cristi and Andrei</author>
void drawBlocksMenu(const BlockMenu& m);

/// <summary>
/// Draws the menu
/// </summary>
/// <param name="m">The menu struct</param>
/// <author>Cristi and Andrei</author>
void drawMenu(const Menu& m);

/// <summary>
/// Checks for updates in the Block menu
/// </summary>
/// <param name="m">The BLock menu struct</param>
/// <param name="m">The global cooldown</param>
/// <author>Andrei and Cristi</author>
Type updateBlockMenu(const BlockMenu& m,const updatedMenu& u, double& cooldown);

/// <summary>
/// Checks for updates in the menu
/// </summary>
/// <param name="m">The menu struct</param>
/// <param name="m">The global cooldown</param>
/// <author>Andrei and Cristi</author>
menuButtons updateMenu(Menu& m, updatedMenu& u, double& cooldown);

/// <summary>
/// Pseudo-constructor for the  menu
/// </summary>
/// <returns>The button</returns>
/// <author>Andrei and Cristi</author>
Button makeButton(double posX, menuButtons type);

/// <summary>
/// Draws the button
/// </summary>
/// <param name="m">The button struct</param>
/// <author>Cristi</author>
void drawButton(const Button& m);

/// <summary>
/// Updates the button (makes a function on right click)
/// </summary>
/// <author>Cristi and Andrei</author>
bool updateButton(Button b, updatedMenu& u, double cooldown);

/// <summary>
/// Transforms the type of buttons into a string 
/// </summary>
/// <author>Andrei</author>
std::string buttonTypeToString(menuButtons type);

/// <summary>
/// Pseudo-constructor for the  windows of the menu
/// </summary>
/// <author>Cristi</author>
updatedMenu makeUpdatedMenu(menuButtons u);

/// <summary>
/// Draws the  windows of the menu
/// </summary>
/// <author>Cristi</author>
void drawUpdatedMenu(const updatedMenu a,std::vector<Block> blocks);

/// <summary>
/// Pseudo-constructor for the questions from Help
/// </summary>
/// <author>Cristi</author>
Question makeQuestion(double posY, helpQuestion type);

/// <summary>
/// Draws the questions from Help
/// </summary>
/// <author>Cristi</author>
void drawQuestion(const Question m);

/// <summary>
/// Pseudo-constructor for the  windows of the submenu
/// </summary>
/// <author>Cristi</author>
updatedSubMenu makeQuestion(helpQuestion u);

/// <summary>
/// Draws the  windows of the submenu
/// </summary>
/// <author>Cristi</author>
void drawUpdatedSubMenu(const updatedSubMenu a);

/// <summary>
/// Checks for updates in the menu
/// </summary>
/// <author>Cristi</author>
helpQuestion updateSubMenu(updatedMenu& m, const updatedSubMenu u, double& cooldown,bool onTop);

