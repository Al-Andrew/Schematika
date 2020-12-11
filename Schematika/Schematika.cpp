#include "Schematika.hpp"
int main()
{
    slWindow( WINDOW_WIDTH, WINDOW_HEIGHT , WINDOW_TITLE , false);
    setBackColor(BACKGROUND_COLOR);
    slSetFont(slLoadFont("./res/Fonts/OpenSans-Regular.ttf"), 24);
    slSetTextAlign(SL_ALIGN_CENTER);
    double cooldown = 0;
    Menu menu = makeMenu();
    std::vector<Block> blocks;
    std::vector<Node*> nodes;
    //You should always have one start block so we add it in from the getgo
    blocks.push_back(generateStart());

    while (!slShouldClose())
    {   
        drawMenu(menu);
        if (Type u = updateMenu(menu, cooldown); u != Type::NOT_A_BLOCK)
        {
            blocks.push_back(generate(u));
        }

        for (Block& bl : blocks)
        {
            draw(bl);
            update(bl, cooldown);
        }
        slRender();
    }
    slClose();
    return 0;
}