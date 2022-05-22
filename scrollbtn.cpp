#include "button.hpp"
#include "listbox.hpp"

using namespace genv;

void Scrollbutton::set_limits()
{
    _toplimit = _parent->get_y()+_parent->get_contour();
    _bottomlimit = _parent->get_y()+_parent->get_height()-_parent->get_contour();
}

void Scrollbutton::toggle_visibility()
{
    if(_visible) _w->delete_widget(this);
    else _w->add_widget(this);

    _visible = !_visible;
}

bool Scrollbutton::is_over(int ex, int ey)
{
    if(ex > _x && ey > _y && ex < _x+_sizex && ey < _y+_sizey)
    {
        _press = true;
        _gy = ey - _y;
        return true;
    }

    _press = false;
    return false;
}

void Scrollbutton::logic(event& ev)
{
    if(ev.button == -btn_left)
        _press = false;

    // mozgatas
    if(_press)
        _y = ev.pos_y - _gy;
    else if(ev.button == btn_wheelup && (_parent->is_in_focus() || _in_focus))
        _y -= _parent->get_linspace();
    else if(ev.button == btn_wheeldown && (_parent->is_in_focus() || _in_focus))
        _y += _parent->get_linspace();

    // mozgas limitalasa
    check_limits();

    // lista eltolasa
    if(_in_focus && (_press || ev.button == btn_wheeldown || ev.button == btn_wheelup))
            _parent->change_scrollvalue((_y-_parent->get_y()-_parent->get_contour())/_parent->get_linspace());

}

void Scrollbutton::check_limits()
{
    if(_y+_sizey >= _bottomlimit)
        _y = _bottomlimit-_sizey;
    else if(_y <= _toplimit)
        _y = _toplimit;
}

void Scrollbutton::draw() const
{
    gout << color(80, 80, 120)
         << move_to(_x, _y)
         << box(_sizex, _sizey);
}
