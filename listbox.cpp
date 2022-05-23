#include "listbox.hpp"
#include "graphics.hpp"
#include <cmath>

using namespace genv;

Listbox::Listbox(Window * w, int x, int y, int sizex, int sizey, std::string title, std::vector<std::string> items) : Widget(w, x, y, sizex, sizey, title), _items(items), _selected(0), _scrollvalue(0)
{
    if(_lineheight * int(items.size()) > sizey)
    {
        _linspace = sizey / items.size();
        _scrollbox = new Scrollbutton(w, x+sizex-_scrollwidth+_contour, y+_contour, _scrollwidth-2*_contour, sizey - _linspace * (abs(sizey - _lineheight* (int(items.size())+1))/_lineheight)-2*_contour, this);
    }
    else
    {
        _linspace = 0;
        _scrollbox = new Scrollbutton(w, x+sizex-_scrollwidth+_contour, y+_contour, _scrollwidth-2*_contour, sizey, this);
        _scrollbox->toggle_visibility();
    }
}

void Listbox::delete_element(std::string element)
{
    std::vector<std::string> new_list;
    for(std::string& s: _items)
    {
        if(s != element) new_list.push_back(s);
    }
    _items = new_list;

    check_list();
    _scrollbox->check_limits();
}

void Listbox::delete_current_element()
{
    if(_items.size() == 0) return;

    std::vector<std::string> new_list;
    for(int i = 0; i < int(_items.size()); i++)
        if(i != _selected) new_list.push_back(_items[i]);

    _items = new_list;
    _selected--;

    check_list();
    _scrollbox->check_limits();
}

void Listbox::add_new(std::string s)
{
    if(s != "") _items.push_back(s);
    check_list();
    _scrollbox->check_limits();
}


void Listbox::draw() const
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

            gout << move_to(_x+gout.cascent(), _y+(i-_scrollvalue)*_lineheight-(_lineheight-gout.cascent())/2+gout.cdescent()*2);
            gout << text(_items[i]);
        }
        else
            i = _items.size();
    }

    // csuszka hatter
    if(_scrollbox->is_visible())
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

void Listbox::check_list()
{
    if(_lineheight * int(_items.size()) > _sizey)
    {
        _linspace = _sizey / _items.size();
        _scrollbox->change_sizey(_sizey - _linspace * (abs(_sizey - _lineheight* (int(_items.size())+1))/_lineheight)-2*_contour);

        if(!_scrollbox->is_visible()) _scrollbox->toggle_visibility();
    }
    if(_lineheight * int(_items.size()) < _sizey && _scrollbox->is_visible()) _scrollbox->toggle_visibility();
}

std::string Listbox::out_value() const
{
    if(_selected < int(_items.size())) return _items[_selected];
    else return "";
}

void Listbox::logic(event& ev)
{
    // gorgetes es huzas
    if(_scrollbox->is_visible() && (ev.button == btn_wheeldown || ev.button == btn_wheelup))
    {
        _scrollbox->logic(ev);
        _scrollvalue = (_scrollbox->get_y()-_y-_contour)/_linspace;
    }
    else if(_scrollbox->is_visible() && _scrollbox->press_logic())
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

    if(ev.keycode == key_down)
    {
        _selected++;
        if(_selected > _items.size()-1) _selected = _items.size()-1;

        if(_lineheight * (_selected+1) > _sizey) 
        {
            _scrollbox->change_y(_linspace);
            change_scrollvalue((_scrollbox->get_y()-_y-_contour)/_linspace);
        }
    }

    if(ev.keycode == key_up)
    {
        _selected--;
        if(_selected < 0) _selected = 0;

        
        if(_selected == _scrollvalue-1)
        {
            _scrollbox->change_y(-_linspace);
            change_scrollvalue((_scrollbox->get_y()-_y-_contour)/_linspace);
        }
    }
}
