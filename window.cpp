#include "window.hpp"

using namespace genv;

void Window::select_widget(Widget *&w)
{
    if(obj_in_focus != nullptr)
        obj_in_focus->toggle_focus();
    w->toggle_focus();
    obj_in_focus = w;
}

void Window::event_loop()
{
    setup();

    event ev;
    while(gin >> ev && ev.keycode != key_escape)
    {
        gout << color(200, 200, 255)
         << move_to(0,0)
         << box(XX, YY);

        // kijeloles
        if(ev.button == btn_left)
        {
            bool found = false;
            for(Widget* w: _widgets)
            {
                if(w->is_over(ev.pos_x, ev.pos_y))
                {
                    select_widget(w);
                    found = true;
                }
            }

            // nem widgetre kattintas
            if(!found && obj_in_focus != nullptr)
            {
                obj_in_focus->toggle_focus();
                obj_in_focus = nullptr;
            }
        }

        // egyeb esemenyek
        if(obj_in_focus != nullptr && (ev.keycode > 0 || ev.type == ev_mouse))
        {
            obj_in_focus->logic(ev);
        }

        for(Widget* w: _widgets)
            w->draw();

        gout << refresh;
    }

}

void Window::setup() const
{
    gout.open(XX,YY);
    gout << font("LiberationSans-Regular.ttf", basic_font_size);
    gout << move_to(0,0) << color(200, 200, 255) << box(XX,YY);

    for(Widget* w: _widgets)
            w->draw();

    gout << refresh;
}

void Window::delete_widget(Widget* w)
{
    std::vector<Widget*> _new_widgets;
    for(Widget* &widget: _widgets)
    {
        if(widget != w) _new_widgets.push_back(widget);
    }
    if(obj_in_focus == w) obj_in_focus = nullptr;

    _widgets = _new_widgets;
}
