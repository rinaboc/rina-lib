#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "window.hpp"
#include <functional>

using namespace genv;

class Button : public Widget
{
protected:
    bool _press;
public:
    Button(Window * w, int x, int y, int sizex, int sizey, std::string title) : Widget(w, x, y, sizex, sizey, title), _press(false){}

    void toggle_press(){_press = !_press;}
    int press_logic()const {return _press;};
    void draw() const override;
    void logic(genv::event&) override;
};

class Checkbox : public Button
{
protected:
    const int border = 3;
public:
    Checkbox(Window * w, int x, int y, int sizex, int sizey) : Button(w, x, y, sizex, sizey, "") {}

    void draw() const override;
    void logic(genv::event&) override;
};

class FButton : public Button
{
protected:
    std::function<void()> _f;
public:
    FButton(Window * w, int x, int y, int sizex, int sizey, std::string s, std::function<void()> f) : Button(w, x, y, sizex, sizey, s), _f(f) {}

    void logic(genv::event& ev) override
    {
        if(ev.button == btn_left)
            _press = true;
        else if(ev.button == -btn_left && _press == true)
        {
            _press = false;
            action();
        }
    }
    virtual void action(){_f();}
};

class Spinbox;

class Arrowbutton : public Button
{
protected:
    int _state;
    Spinbox * _parent;
public:
    Arrowbutton(Window * w, int x, int y, int sizex, int sizey, Spinbox * parent) : Button(w, x, y, sizex, sizey, ""), _state(0), _parent(parent){}

    void draw() const override;
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
    bool _visible;
public:
    Scrollbutton(Window * w, int x, int y, int sizex, int sizey, Listbox * parent) : Button(w, x, y, sizex, sizey, ""), _gy(0), _parent(parent), _toplimit(0), _bottomlimit(0)
    {
        set_limits();
        _visible = true;
    }

    void set_limits();
    void check_limits();
    void draw() const override;
    bool is_over(int, int) override;
    void logic(genv::event&) override;
    void toggle_visibility();
    void change_sizey(int newsizey) {_sizey = newsizey;}
    bool is_visible()const {return _visible;}
};

class Mixbutton : public Button
{
protected:
    Listbox * _parent;
    Listbox * _destination;
public:
    Mixbutton(Window * w, int x, int y, int sizex, int sizey, std::string arrow , Listbox * parent, Listbox * destination) : Button(w, x, y, sizex, sizey, arrow), _parent(parent), _destination(destination){}

    void logic(genv::event&) override;
};

#endif // BUTTON_HPP
