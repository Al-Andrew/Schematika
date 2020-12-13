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
        if (nod != n && nod->host != nullptr &&isCircleInCircle(n->x, n->y, n->r, nod->x, nod->y, nod->r))
            return nod;
    }
    return nullptr;
}
