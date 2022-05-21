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

void Spinbox::draw() const
{
    title_draw();

    if(_in_focus)
    {
        gout << color(240,240,255)
             << move_to(_x-_selection_line, _y-_selection_line) << box(_sizex+2*_selection_line, _sizey+2*_selection_line);
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
        << move_to(_x+(_sizex-_controlwidth-gout.twidth(_text))/2, _y+(_sizey-(gout.cdescent()+gout.cascent()))/2)
        << text(_text);
}
