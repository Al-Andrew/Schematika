#include "helpers.hpp"
#include "sl.h"


/** \brief Checks if the mouse is in a rectangle
 *
 * \param The atributes of the rectangle being checked
 * \return boolean if the mouse is bound or not
 * @Andrei
 */
bool isMouseInRect(double x, double y, double width, double height)
{
    double mx = slGetMouseX();
    double my = slGetMouseY();
    return (mx >= x - width/2.f && mx <= x + width/2.f) && (my >= y - height/2.f && my <= y + height/2.f);
}

/** \brief Checks if the mouse is in a circle
 *
 * \param The atributes of the circle being checked
 * \return boolean if the mouse is bound or not
 * @Andrei
 */
bool isMouseInCircle(double x, double y, double r)
{
    double mx = slGetMouseX();
    double my = slGetMouseY();
    double dist = sqrt( (mx - x)*(mx - x) + (my - y)*(my - y) );
    return dist <= r;
}
/** \brief Checks for the colision of two circles
 *
 * \param The atributes of the circles being checked
 * \return boolean if the circles colide or not
 * @Andrei
 */
bool isCircleInCircle(double x1, double y1, double r1, double x2, double y2, double r2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= (r1+r2)*(r1+r2);
}

/** \brief Checks for a click in a given rect
 *
 * \param The atributes of the rect being checked
 * \return boolean if the react has been clicked or not
 * @Cristi
 */
bool isRectClicked(double x, double y, double width,double height)
{
    return slGetMouseButton(SL_MOUSE_BUTTON_LEFT) && isMouseInRect(x,y,width,height);
}

/** \brief Checks for a click in a given circle
 *
 * \param The atributes of the circle being checked
 * \return boolean if the circle has been clicked or not
 * @Cristi
 */
bool isCircleClicked(double x, double y, double r)
{
    return slGetMouseButton(SL_MOUSE_BUTTON_LEFT) && isMouseInCircle(x,y,r);
}

/** \brief Sets the foreground color
 *
 * \param The color to be set
 * @Andrei
 */
void setForeColor(Color c)
{
    slSetForeColor(c.r/255.f, c.g/255.f, c.b/255.f, c.a);
}

/** \brief Sets the limits of the floating blocks
 *
 * \param The limit to be set
 * @Cristi
 */
void limitsOfFloatingBlocks(Block & b)
{
     if(slGetMouseX()<BLOCK_LIMITS_LEFT && slGetMouseY()<BLOCK_LIMITS_DOWN)
    {
       b.x=BLOCK_LIMITS_LEFT;
       b.y=BLOCK_LIMITS_DOWN;
    }
    else if(slGetMouseX()<BLOCK_LIMITS_LEFT && slGetMouseY()>BLOCK_LIMITS_UP)
    {
       b.x=BLOCK_LIMITS_LEFT;
       b.y=BLOCK_LIMITS_UP;
    }
    else if(slGetMouseX()<BLOCK_LIMITS_LEFT)
    {
       b.x=BLOCK_LIMITS_LEFT;
    }
    else if(slGetMouseX()>BLOCK_LIMITS_RIGHT && slGetMouseY()<BLOCK_LIMITS_DOWN)
    {
       b.x=BLOCK_LIMITS_RIGHT;
       b.y=BLOCK_LIMITS_DOWN;
    }
    else if(slGetMouseX()>BLOCK_LIMITS_RIGHT && slGetMouseY()>BLOCK_LIMITS_UP)
    {
       b.x=BLOCK_LIMITS_RIGHT;
       b.y=BLOCK_LIMITS_UP;
    }
    else if(slGetMouseX()>BLOCK_LIMITS_RIGHT)
    {
       b.x=BLOCK_LIMITS_RIGHT;
    }
    else if(slGetMouseY()<BLOCK_LIMITS_DOWN)
    {
       b.y=BLOCK_LIMITS_DOWN;
    }
    else if(slGetMouseY()>BLOCK_LIMITS_UP)
    {
       b.y=BLOCK_LIMITS_UP;
    }
}

/// <summary>
/// Increments the cooldown to sync actions in the window
/// </summary>
/// <param name="cooldown"></param>
/// @Cristi
void setCooldown(double & cooldown)
{
    cooldown = slGetTime() + ACTION_COOLDOWN;
}
