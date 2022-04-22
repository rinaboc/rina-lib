#include "button.hpp"
#include "spinbox.hpp"
#include <iostream>

using namespace genv;

bool Arrowbutton::is_over(int ex, int ey)
{
    if(_x < ex && _x+_sizex*2 > ex && _y < ey && _y+_sizex > ey)
    {
        _state = 1;
        _press = true;
        return true;
    }
    else if(_x < ex && _x+_sizex*2 > ex && _y+_sizex < ey && _y+_sizex*2 > ey)
    {
        _state = -1;
        _press = true;
        return true;
    }
    _press = false;
    return false;
}

void Arrowbutton::logic(event& ev)
{
    if(_press)
    {
        _parent->change_value(_state);
        if(!_parent->is_in_focus())
            _parent->toggle_focus();
        toggle_press();
    }

    if(ev.button == -btn_left || !(_x < ev.pos_x && _x+_sizex*2 > ev.pos_x && _y < ev.pos_y && _y+_sizex*2 > ev.pos_y))
    {
        _state = 0;
        if(_parent->is_in_focus() && !(_x < ev.pos_x && _x+_sizex*2 > ev.pos_x && _y < ev.pos_y && _y+_sizex*2 > ev.pos_y))
            _parent->toggle_focus();
    }

}

void Arrowbutton::draw()
{
    if(!_in_focus || _state == 0)
    {
        gout
            << color(140, 140, 255)
            << move_to(_x, _y)
            << box(_sizex*2, _sizey*2);
    }


    if(_in_focus)
    {
        if(_state == 1)
        {
            gout
                << color(180, 180, 255)
                << move_to(_x, _y)
                << box(_sizex*2, _sizey);

            gout
                << color(140, 140, 255)
                << move_to(_x, _y+_sizey)
                << box(_sizex*2, _sizey);
        }
        if(_state == -1)
        {
            gout
                << color(180, 180, 255)
                << move_to(_x, _y+_sizey)
                << box(_sizex*2, _sizey);

            gout
                << color(140, 140, 255)
                << move_to(_x, _y)
                << box(_sizex*2, _sizey);
        }
    }

    if(_state == 1) gout << color(140, 140, 255);
    else gout << color(80, 80, 120);
    for (int i = -_sizex/2+1; i < _sizex/2; i++)
    {
        gout << move_to(_x + _sizex/2 + i, _y + _sizey/2 - i) << line(_sizex - 2*i, 0);
    }


    if(_state == -1) gout << color(140, 140, 255);
    else gout << color(80, 80, 120);
    for (int i = -_sizex/2+1; i < _sizex/2; i++)
    {
        gout << move_to(_x + _sizex/2 + i, _y + _sizey + _sizey/2 + i) << line(_sizex - 2*i, 0);
    }
}
