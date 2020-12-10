#include "sl.h"
#include "blocks.hpp"
#include "config.hpp"
#include "helpers.hpp"
#include<iostream>


Block generateStart()
{
    Block b;
    b.type = Type::START;
    b.x=DEFAULT_X;
    b.y=DEFAULT_Y;
    b.width=START_WIDTH;
    b.height=START_HEIGHT;
    b.floating = false;

    return b;
}
Block generateStop()
{
    Block b;
    b.type= Type::STOP;
    b.x=DEFAULT_X;
    b.y=DEFAULT_Y;
    b.width=STOP_WIDTH;
    b.height=STOP_HEIGHT;
    b.floating = false;

    return b;
}
Block generateInput()
{
    Block b;
    b.type= Type::INPUT;
    b.x=DEFAULT_X;
    b.y=DEFAULT_Y;
    b.width=IN_WIDTH;
    b.height=IN_HEIGHT;
    b.floating = false;

    return b;
}
Block generateOutput()
{
    Block b;
    b.type= Type::OUTPUT;
    b.x=DEFAULT_X;
    b.y=DEFAULT_Y;
    b.width=OUT_WIDTH;
    b.height=OUT_HEIGHT;
    b.floating = false;

    return b;
}
Block generateCalcul()
{
    Block b;
    b.type = Type::CALCUL;
    b.x=DEFAULT_X;
    b.y=DEFAULT_Y;
    b.width=CALCUL_WIDTH;
    b.height=CALCUL_HEIGHT;
    b.floating = false;

    return b;
}

void drawStart(const Block& b)
{
    slSetForeColor(BLOCK_FILL_COLOR,255);
    slCircleFill(b.x-34,b.y,b.height/2,20);
    slRectangleFill(b.x,b.y,b.width-30,b.height);
    slCircleFill(b.x+34,b.y,b.height/2,20);
    slSetForeColor(BLOCK_TEXT_COLOR,255);
    slText(b.x+5,b.y-10,"START");
}
void drawStop(const Block& b)
{
    slSetForeColor(BLOCK_FILL_COLOR,255);
    slCircleFill(b.x-34,b.y,b.height/2,20);
    slRectangleFill(b.x,b.y,b.width-30,b.height);
    slCircleFill(b.x+34,b.y,b.height/2,20);
    slSetForeColor(BLOCK_TEXT_COLOR,255);
    slText(b.x+5,b.y-10,"STOP");
}
void drawInput(const Block& b)
{
    slSetForeColor(BLOCK_FILL_COLOR,255);
    for(int i=0;i<IN_WIDTH;i++)
    {
        slLine(b.x-60 +i, b.y, b.x-40+i, b.y+IN_HEIGHT);
    }
    slSetForeColor(BLOCK_TEXT_COLOR,255);
    slText(b.x,b.y+15,"IN");
}
void drawOutput(const Block& b)
{
    slSetForeColor(BLOCK_FILL_COLOR,255);
    for(int i=0;i<OUT_WIDTH;i++)
    {
        slLine(b.x-60 +i, b.y, b.x-40+i, b.y+OUT_HEIGHT);
    }
    slSetForeColor(BLOCK_TEXT_COLOR,255);
    slText(b.x,b.y+15,"IN");
}
void drawCalcul(const Block& b)
{
     slSetForeColor(BLOCK_FILL_COLOR,255);
     slRectangleFill(b.x,b.y,CALCUL_WIDTH,CALCUL_HEIGHT);
     slSetForeColor(BLOCK_TEXT_COLOR,255);
     slText(b.x,b.y-10,"CALCUL");
}
void drawDecizie(const Block& b)
{
    slSetForeColor(BLOCK_FILL_COLOR, 255);
    slTriangleFill(b.x,b.y,DECIZIE_WIDTH,DECIZIE_HEIGHT);
    slSetForeColor(BLOCK_DECIZIE_DA_COLOR,255);
    slRectangleFill(b.x-55,b.y,25,25);
    slSetFontSize(15);
    slSetForeColor(BLOCK_DECIZIE_TEXT_COLOR, 255);
    slText(b.x-55,b.y-5,"DA");
    slSetForeColor(BLOCK_DECIZIE_NU_COLOR, 255);
    slRectangleFill(b.x+55,b.y,25,25);
    slSetForeColor(BLOCK_DECIZIE_TEXT_COLOR, 255);
    slText(b.x+55,b.y-5,"NU");
    slSetForeColor(BLOCK_TEXT_COLOR, 255);
    slSetFontSize(20);
    slText(b.x,b.y-20,"DECIZIE");
}


void draw(const Block& b)
{
    switch (b.type)
    {
    case START:
        drawStart(b);
        break;
    case CALCUL:
        drawCalcul(b);
        break;
    case DECIZIE:
        drawDecizie(b);
        break;
    case INPUT:
        drawDecizie(b);
        break;
    case OUTPUT:
        drawOutput(b);
        break;
    case STOP:
        drawStop(b);
        break;
    default:
        break;
    }
}

void update(Block& b, double& cooldown)
{
    if (b.floating)
    {
        b.x = slGetMouseX();
        b.y = slGetMouseY();
        limitsOfFloatingBlocks(b);
    }
    if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT) and isMouseInRect(b.x, b.y, b.width, b.height) and cooldown < slGetTime())
    {
        b.floating = !b.floating;
        setCooldown(cooldown);
    }
}