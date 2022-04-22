#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include <string>

class Window;

class Widget
{
protected:
    Window* _w;
    int _x, _y, _sizex, _sizey;
    std::string _title;
    bool _in_focus;
public:
    Widget(Window*, int, int, int, int, std::string);

    virtual void draw() = 0;
    void title_draw();
    void toggle_focus();
    virtual bool is_over(int, int);
    virtual void logic(genv::event&){}
    bool is_in_focus(){return _in_focus;}

};

#endif // WIDGET_HPP
