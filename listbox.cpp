#include "listbox.hpp"
#include "graphics.hpp"
#include <iostream>
using namespace std;

using namespace genv;

Listbox::Listbox(Window * w, int x, int y, int sizex, int sizey, std::string title, std::vector<std::string> items) : Widget(w, x, y, sizex, sizey, title), _items(items), _selected(0), _scrollvalue(0), _linspace(sizey / items.size())
{
    if(_lineheight * int(items.size()) > sizey)
    {
        _scrollbox = new Scrollbutton(w, x+sizex-_scrollwidth+_contour, y+_contour, _scrollwidth-2*_contour, _scrollwidth + ((_sizey-2*_contour)*2)/items.size(), this);
        cout << ((_sizey-2*_contour)*2)/items.size() << endl;
    }
    else
        _scrollbox = nullptr;

}

void Listbox::draw()
{
    title_draw();

    if(_in_focus)
    {
        gout << color(240,240,255)
             << move_to(_x-_selection_line, _y-_selection_line)
             << box(_sizex+2*_selection_line, _sizey+2*_selection_line);
    }

    gout << move_to(_x, _y)
         << color(220, 220, 255)
         << box(_sizex, _sizey);

    // elem kijeloles es hatter
    for (int i = _scrollvalue; i < int(_items.size()); ++i) {
        if(_y+ (i+1-_scrollvalue)*_lineheight < _y+_sizey)
        {
            if(_selected == i)
            {
                gout << move_to(_x, _y+(i-_scrollvalue)*_lineheight)
                     << color(240,240,255)
                     << box(_sizex, _lineheight);
            }

            if(_in_focus && _selected == i) gout << color(80, 80, 120);
            else gout << color(140, 140, 255);

            gout << move_to(_x+gout.cascent(), _y+(i-_scrollvalue)*_lineheight+gout.cascent()+(_lineheight-gout.cascent())/2);
            gout << text(_items[i]);
        }
        else
            i = _items.size();
    }

    // csuszka hatter
    if(_scrollbox != nullptr)
    {
        if(_in_focus)
        {
            gout << color(240,240,255)
                 << move_to(_x+_sizex-_scrollwidth-_selection_line, _y)
                 << box(_selection_line*2, _sizey);
        }

        gout << move_to(_x+_sizex-_scrollwidth, _y)
             << color(140, 140, 255)
             << box(_scrollwidth, _sizey);
    }
}

void Listbox::logic(event& ev)
{
    // gorgetes es huzas
    if(_scrollbox != nullptr && (ev.button == btn_wheeldown || ev.button == btn_wheelup))
    {
        _scrollbox->logic(ev);
        _scrollvalue = (_scrollbox->get_y()-_y-_contour)/_linspace;
        cout << _linspace << " " << _scrollvalue << endl;
    }
    else if(_scrollbox != nullptr && _scrollbox->press_logic())
    {
        _scrollvalue = (_scrollbox->get_y()-_y)/_linspace;
    }


    // elem kijeloles
    if(ev.button == btn_left && ev.pos_x > _x && ev.pos_x < _x+_sizex)
    {
        int i = 0;
        while (i < int(_items.size()) && !(ev.pos_y > _y+i*_lineheight && ev.pos_y < _y+(i+1)*_lineheight)) {
            i++;
        }

        if(i < int(_items.size()))
            _selected = i+_scrollvalue;
    }
}
