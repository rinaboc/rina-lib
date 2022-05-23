#ifndef SPINBOX_HPP
#define SPINBOX_HPP

#include "graphics.hpp"
#include "widget.hpp"
#include "button.hpp"

class Spinbox : public Widget
{
protected:
    int _min, _max;
    int _value;
    std::string _text;
    const int _controlwidth = 20;
    Arrowbutton * _control;
public:
    Spinbox(Window * w, int x, int y, int sizex, std::string title, int minimum, int maximum, int start_value) : Widget(w, x, y, sizex, _controlwidth, title), _min(minimum), _max(maximum), _value(start_value)
    {
        _sizey = _controlwidth;
        if(genv::gout.cascent()+genv::gout.cdescent() > _sizey) // ha tul nagy a font
            _sizey += genv::gout.cascent()+genv::gout.cdescent()-_sizey;

        check_value();
        _text = std::to_string(_value);

        _control = new Arrowbutton(w, _x+_sizex-_controlwidth, _y+(_sizey-_controlwidth)/2, _controlwidth/2, _controlwidth/2, this);
    }

    void draw() const override;
    void change_value(int);
    void logic(genv::event&) override;
    void check_value();
    int out_value() {return _value;}

};

#endif // SPINBOX_HPP
