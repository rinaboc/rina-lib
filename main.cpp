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
    Textbox* tb;
    FButton* fb;

public:
    Test_app()
    {
        lb = new Listbox(this, 50, 50, 150, 150, "Listbox", {});
        sb = new Spinbox(this, 250, 50, 100, 20, "Spinbox", 10,100);
        st = new StaticText(this, 250, 300, 150, 20, "Static Text", 30);
        tb = new Textbox(this, 250, 150, 150, 40, "Textbox", nullptr);

    }
};


int main()
{
    Test_app ta;
    ta.event_loop();
    return 0;
}
