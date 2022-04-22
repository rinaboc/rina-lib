#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"

class Button : public Widget
{
protected:
    bool _press;
public:
    Button(Window * w, int x, int y, int sizex, int sizey, std::string title) : Widget(w, x, y, sizex, sizey, title)
    {
        _press = false;
    }
    void toggle_press(){_press = !_press;}
    int press_logic(){return _press;};
    void draw() override;
};

class Spinbox;

class Arrowbutton : public Button
{
protected:
    int _state;
    Spinbox * _parent;
public:
    Arrowbutton(Window * w, int x, int y, int sizex, int sizey, Spinbox * parent) : Button(w, x, y, sizex, sizey, "")
    {
        _state = 0;
        _parent = parent;
    }

    void draw() override;
    bool is_over(int, int) override;
    void logic(genv::event&) override;
};

class Listbox;

class Scrollbutton : public Button
{
protected:
    int _gy;
    Listbox * _parent;
    int _toplimit;
    int _bottomlimit;
public:
    Scrollbutton(Window * w, int x, int y, int sizex, int sizey, Listbox * parent) : Button(w, x, y, sizex, sizey, "")
    {
        _gy = 0;
        _parent = parent;
        set_limits();
    }

    void set_limits();
    void draw() override;
    bool is_over(int, int) override;
    void logic(genv::event&) override;
    int get_y(){return _y;}
};

#endif // BUTTON_HPP
