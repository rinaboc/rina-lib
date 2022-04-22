#include "button.hpp"

using namespace genv;

void Button::draw()
{
    title_draw();

    if(_in_focus)
    {
        gout << color(140, 140, 255)
             << move_to(_x, _y)
             << box(_sizex, _sizey);
    }

    else
    {
        gout << color(60, 60, 100)
             << move_to(_x, _y)
             << box(_sizex, _sizey)
             << color(80, 80, 120)
             << move_to(_x+2, _y+2)
             << box(_sizex-4, _sizey-4);
    }

}
