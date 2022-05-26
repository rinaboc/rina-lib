#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "widget.hpp"

class Window
{
protected:
    std::vector<Widget*> _widgets;
    Widget * obj_in_focus = nullptr;
    const int XX = 600;
    const int YY = 600;
    const int basic_font_size = 16;
public:
    void add_widget(Widget * w){_widgets.push_back(w);}
    void delete_widget(Widget*);

    void setup() const;
    void event_loop();
    void select_widget(Widget * &);
    int get_font_size()const {return basic_font_size;}

};

#endif // WINDOW_HPP
