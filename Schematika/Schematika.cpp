#include "Schematika.hpp"
int main()
{
    slWindow( WINDOW_WIDTH, WINDOW_HEIGHT , WINDOW_TITLE , false);
    double cooldown = 0;
    //Menu menu;
    std::vector<Block> blocks;
    std::vector<Node*> nodes;
    slSetBackColor(BACKGROUND_COLOR);
    //You should always have one start block so we add it in from the getgo
    blocks.push_back(generateStart());

    while (!slShouldClose())
    {   
        //drawMenu();
        //if(updateMenu(cooldown) != "")
        for (Block& bl : blocks)
        {
            draw(bl);
            update(bl, cooldown);
        }
        if ( slGetKey(SL_KEY_ENTER) and cooldown < slGetTime())
        {
            blocks.push_back(generateCalcul());
            setCooldown(cooldown);
        }
        slRender();
    }
    slClose();
    return 0;
}