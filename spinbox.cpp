#include "spinbox.hpp"

using namespace genv;

void Spinbox::check_value()
{
    if(_value > _max)
        _value = _max;
    else if(_value < _min)
        _value = _min;
}

void Spinbox::change_value(int v)
{
    _value += v;
    check_value();
    _text = std::to_string(_value);
}

void Spinbox::logic(event &ev)
{
    if(ev.keycode == key_up)
    {
        _value += 1;
    }
    else if(ev.keycode == key_down)
    {
        _value -= 1;
    }
    else if(ev.keycode == key_pgup)
    {
        _value += 10;
    }
    else if(ev.keycode == key_pgdn)
    {
        _value -= 10;
    }

    check_value();
    _text = std::to_string(_value);
}

void Spinbox::draw()
{
    title_draw();

    if(_in_focus)
    {
        gout << color(240,240,255)
             << move_to(_x-1, _y-1) << box(_sizex+2, _sizey+2);
    }
    else
    {
        gout
            << color(220, 220, 255)
            << move_to(_x, _y) << box(_sizex, _sizey);
    }

    // ertek kiiras
    gout
        << color(80, 80, 120)
        << move_to(_x+(_sizex-_controlwidth-gout.twidth(_text))/2, _y+_sizey/2+gout.cdescent())
        << text(_text);

    _control->draw();
}
