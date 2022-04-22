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
    Spinbox(Window * w, int x, int y, int sizex, int sizey, std::string title, int min, int max) : Widget(w, x, y, sizex, sizey, title)
    {
        _min = min;
        _max = max;
        _value = min;
        _text = std::to_string(min);
        _control = new Arrowbutton(w, _x+_sizex-_controlwidth, _y, _controlwidth/2, _controlwidth/2, this);
    }

    void draw() override;
    void change_value(int);
    void logic(genv::event&) override;
    void check_value();
    std::string out_value() override {return _text;}

};

#endif // SPINBOX_HPP
