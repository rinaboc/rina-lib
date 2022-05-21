#include "button.hpp"


void Checkbox::draw() const
{
    if(_in_focus)
    {
        gout << color(240,240,255)
             << move_to(_x-_selection_line, _y-_selection_line)
             << box(_sizex+2*_selection_line, _sizey+2*_selection_line);
    }

    gout << color(140, 140, 255)
    << move_to(_x, _y)
    << box(_sizex, _sizey);

    if(_press)
    {
        gout << color(180, 180, 255);
        for(int i = -border; i < border; i++)
        {
            gout << move_to(_x+border, _y+border+i) << line(_sizex-2*border, _sizey-2*border);
            gout << move_to(_x+border, _y+_sizey-border+i) << line(_sizex-2*border, -_sizey+2*border);
        }
    }
    
}

void Checkbox::logic(genv::event& ev)
{
    if(ev.button == btn_left)
        toggle_press();
}