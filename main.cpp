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

public:
    Test_app()
    {
        lb = new Listbox(this, 50, 50, 150, 150, "Listbox", {"alma", "korte"});
        sb = new Spinbox(this, 250, 50, 100, 20, "Spinbox", 10,100);
        st = new StaticText(this, 250, 300, 150, 20, "Static Text", 30);
        fb = new FButton(this, 430, 150, 100, 40, "hozzaad", [=](){lb->add_new(tb->get_text()); tb->clear_text();});
        tb = new Textbox(this, 250, 150, 150, 40, "Textbox", fb);

        cb = new Checkbox(this, 250, 80, 30, 30);
    }
};


int main()
{
    Test_app ta;
    ta.event_loop();
    return 0;
}
