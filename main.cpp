#include "listbox.hpp"
#include "spinbox.hpp"
#include "widget.hpp"
#include "window.hpp"
#include "statictext.hpp"
#include "textbox.hpp"

struct Test_app : public Window
{
protected:
    Listbox* lb;
    Spinbox* sb;
    StaticText* st;
    FButton* fb;
    Textbox* tb;
    Checkbox* cb;
    FButton* fb2;
    Listbox* lb2;
    FButton* mix1;
    FButton* mix2;

public:
    Test_app()
    {
        lb = new Listbox(this, 50, 50, 150, 100, "Listbox", {"alma", "szilva", "ananasz"});
        sb = new Spinbox(this, 250, 50, 100, "Spinbox", 10,100, 50);
        st = new StaticText(this, 250, 300, 150, 20, "Static Text", 30);
        fb = new FButton(this, 430, 150, 100, 40, "hozzáad", [=](){lb->add_new(tb->get_text()); tb->clear_text();});
        tb = new Textbox(this, 250, 150, 150, 40, "Textbox", fb);
        cb = new Checkbox(this, 250, 80, 30, 30);
        fb2 = new FButton(this, 50,160, 100, 30, "töröl", [=](){lb->delete_current_element();});

        lb2 = new Listbox(this, 50, 250, 150, 100, "Listbox2", {"1", "2", "3"});
        mix1 = new FButton(this, 50, 370, 30, 30, "/\\", [=](){lb->add_new(lb2->out_value()); lb2->delete_current_element();});
        mix1 = new FButton(this, 100, 370, 30, 30, "\\/", [=](){lb2->add_new(lb->out_value()); lb->delete_current_element();});
    }
};


int main()
{
    Test_app ta;
    ta.event_loop();
    return 0;
}
