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
    gout << font("LiberationSans-Regular.ttf", 16);
    gout << move_to(0,0) << color(200, 200, 255) << box(600,600);
    gout << refresh;
}

struct Screen : public Window
{
protected:
    Listbox * widget1;
    Listbox * widget2;
    Mixbutton * jobbwidget;
    Mixbutton * balwidget;

public:
    Screen()
    {
        // teszt lista generalas
        std::vector<std::string> items;
        for(int i = 1; i < 5; i++)
            items.push_back("balelem "+std::to_string(i));

        std::vector<std::string> items2;
        for(int i = 1; i < 5; i++)
            items2.push_back("jobbelem "+std::to_string(i));


        widget1 = new Listbox(this, 50, 40, 200, 200, "elem kivalaszto 1", items);
        widget2 = new Listbox(this, 340, 40, 200, 200, "elem kivalaszto 2", items2);

        jobbwidget = new Mixbutton(this, 260, 40, 30,30, ">", widget1, widget2);
        balwidget = new Mixbutton(this, 300, 40, 30,30, "<", widget2, widget1);
    }

    void output_data() override
    {
//        if(widget3->press_logic())
//        {
//            std::ofstream f("output.log");
//
//            f << widget1->get_title() << ": " << widget1->out_value() << std::endl;
//            f << widget2->get_title() << ": " << widget2->out_value() << std::endl;
//            f << widget4->get_title() << ": " << widget4->out_value() << std::endl;
//            f << widget5->get_title() << ": " << widget5->out_value() << std::endl;
//
//            f.close();
//
//            widget3->toggle_press();
//        }
    }
};


int main()
{
    setup();
    Screen s;
    s.event_loop();
    return 0;
}
