#include "graphics.hpp"
#include "listbox.hpp"
#include "spinbox.hpp"
#include "widget.hpp"
#include "window.hpp"
#include <fstream>

using namespace genv;
using namespace std;

void setup()
{
    gout.open(600,600);
    gout << move_to(0,0) << color(200, 200, 255) << box(600,600);
    gout << refresh;
}

struct Screen : public Window
{
protected:
    Spinbox * widget1;
    Spinbox * widget2;
    Button * widget3;
    Listbox * widget4;
    Listbox * widget5;

public:
    Screen()
    {
        widget1 = new Spinbox(this, 30, 40, 150, 20, "szambeallito 1", -100, 100);
        widget2 = new Spinbox(this, 30, 90, 80, 20, "szambeallito 2", 20, 40);
        widget3 = new Button(this, 30, 150, 60, 20, "Gomb");

        std::vector<std::string> items;
        for(int i = 1; i < 5; i++)
            items.push_back("elem "+std::to_string(i));

        widget4 = new Listbox(this, 300, 40, 200, 100, "elem kivalaszto 1", items);

        std::vector<std::string> items2;
        for(int i = 1; i < 28; i++)
            items2.push_back("elem "+std::to_string(i));

        widget5 = new Listbox(this, 300, 200, 150, 300, "elem kivalaszto 2", items2);
    }

    void output_data() override
    {
        if(widget3->is_in_focus())
        {
            std::ofstream f("output.log");
            f << widget1->out_value() << " " << widget2->out_value() << std::endl;
            f << widget4->out_value() << " " << widget5->out_value();
            f.close();

            widget3->toggle_focus();
            obj_in_focus = nullptr;
        }
    }
};


int main()
{
    setup();
    Screen s;
    s.event_loop();
    return 0;
}
