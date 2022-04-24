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
    Spinbox(Window * w, int x, int y, int sizex, int sizey, std::string title, int minimum, int maximum) : Widget(w, x, y, sizex, sizey, title), _min(minimum), _max(maximum), _value(minimum), _text(std::to_string(minimum))
    {
        _control = new Arrowbutton(w, _x+_sizex-_controlwidth, _y+(_sizey-_controlwidth)/2, _controlwidth/2, _controlwidth/2, this);
    }

    void draw() override;
    void change_value(int);
    void logic(genv::event&) override;
    void check_value();
    int out_value() {return _value;}

};

#endif // SPINBOX_HPP
