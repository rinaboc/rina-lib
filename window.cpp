#include "window.hpp"
#include "graphics.hpp"
#include "widget.hpp"

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
    for(Widget* w: _widgets)
    {
        w->draw();
    }
    gout << refresh;

    event ev;
    while(gin >> ev && ev.keycode != key_escape)
    {
        gout << move_to(0,0) << color(200, 200, 255) << box(600,600);

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

        output_data();
    }
}
