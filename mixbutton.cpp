#include "button.hpp"
#include "listbox.hpp"

using namespace genv;

void Mixbutton::logic(event& ev)
{
    if(ev.button == btn_left)
    {
        _destination->add_new(_parent->out_value());
        _parent->delete_element(_parent->out_value());
        toggle_press();
//        _destination->check_list();
//        _parent->check_list();
    }
    if(ev.button == -btn_left) toggle_press();
}
