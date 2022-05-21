#include "textbox.hpp"
#include "graphics.hpp"
#include <iostream>
using namespace genv;
using namespace std;

Textbox::Textbox(Window * w, int x, int y, int sx, int sy, string t, FButton* fb)
    : Widget(w, x,y,sx,sy, t), _fbutton(fb)
{
    _text="";
    _cursor = 0;
}

void Textbox::draw() const
{
    title_draw();

    gout << move_to(_x, _y) << color(255,255,255) << box(_sizex, _sizey);

    if(_in_focus)
    {
        gout
        << move_to(_x+_selection_line, _y+_selection_line)
        << color(220, 220, 255)
        << box(_sizex-2*_selection_line, _sizey-2*_selection_line);
    }
    else{
        gout
        << move_to(_x, _y)
        << color(220, 220, 255)
        << box(_sizex, _sizey);
    }

    /// text
    gout
    << move_to(_x+(_sizex-gout.twidth(_text))/2, _y+(_sizey-(gout.cdescent()+gout.cascent()))/2)
    << color(140, 140, 255)
    << text(_text);

    /// cursor
    if(_text.length()>0)
    {
        gout << color(80, 80, 120);
        string temptext = "";
        for(int i = 0; i < _cursor+1; i++)
        {
            temptext += _text[i];
        }
       gout
        << move_to(_x+(_sizex - gout.twidth(_text))/2 +gout.twidth(temptext), _y + (_sizey + gout.cascent())/2)
        << line(0, -gout.cdescent()-gout.cascent());
    }

//    if(_text.length()>0)
//    {
//       gout
//        << move_to(_x+(_sizex - gout.twidth(_text))/2 + (gout.twidth(_text)/_text.length()*_cursor), _y + _sizey/2 + gout.cascent()/2)
//        << line(gout.twidth(string(1,_text[_cursor])), 0);
//    }

}

void Textbox::check_cursor()
{
    if(_cursor < 0) _cursor = 0;
    if(_cursor > int(_text.length())) _cursor = _text.length();
}

bool Textbox::move_cursor(event& ev)
{
    if(ev.keycode == key_left)
    {
        _cursor--;
        check_cursor();
        return true;
    }
    if(ev.keycode == key_right)
    {
        _cursor++;
        check_cursor();
        return true;
    }
    return false;
}

void Textbox::logic(event& ev)
{
    if(move_cursor(ev)) return;

    if(ev.keycode == key_backspace)
    {
        remove_text();
        return;
    }

    if(abs(ev.keycode) == key_lshift || abs(ev.keycode) == key_rshift)
    {
        while(gin >> ev && ev.type != ev_key && !(abs(ev.keycode) != key_right) && !(abs(ev.keycode) != key_backspace) && (ev.keycode != -key_lshift || ev.keycode != -key_rshift)){}
        string button = ev.keyutf8;
        add_text(button);
        return;
    }

    if(ev.keycode == key_enter)
    {
        if(_fbutton != nullptr) _fbutton->action();
        clear_text();
        return;
    }

    if(ev.type == ev_key && ev.keycode > 0)
    {
        add_text(ev.keyutf8);
    }
}

void Textbox::add_text(string s)
{
    if(_text.length() == 0)
        _text = s;
    else if(_cursor == -1)
    {
        _text = s + _text;
        _cursor++;
    }

    else{
        if(_x+(_sizex - gout.twidth(_text))/2 + gout.twidth(_text) + _textborder < _x + _sizex - _textborder)
        {
            string uj_szo;
            for(int i = 0; i < int(_text.length())+1; i++)
            {
                uj_szo += _text[i];
                if(i == _cursor)
                    uj_szo += s;

            }
            if(_cursor < _text.length())
                _cursor++;

            uj_szo.pop_back();
            _text = uj_szo;
        }
    }


    while(_x+(_sizex - gout.twidth(_text))/2 + gout.twidth(_text) + _textborder > _x + _sizex - _textborder)
    {
        _text.pop_back();
        _cursor = _text.length()-1;

//        _size_x += gout.twidth(s);
    }
//    cout << _text.length() << "\t" << s << endl;

}

void Textbox::remove_text()
{
    if(_text.length() > 0)
    {
//        _size_x -= gout.twidth(string(1, _text[_text.length()-1]));

        string uj_szo;
        for(int i = 0; i < _text.length(); i++)
        {
            if(i != _cursor) uj_szo += _text[i];
        }
        _text = uj_szo;

        if(_cursor > -1)
            _cursor--;
    }
    else
    {
        _cursor = 0;
    }


    cout << _cursor << endl;
}
