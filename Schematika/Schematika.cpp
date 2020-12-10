#include "Schematika.hpp"

int main()
{
    slWindow(400, 400, "Schematika", false);

    while (!slShouldClose())
    {
        slRender();
    }
    slClose();
    return 0;
}