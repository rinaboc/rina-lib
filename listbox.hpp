#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "button.hpp"
#include "widget.hpp"

class Listbox : public Widget
{
protected:
    std::vector<std::string> _items;
    const int _lineheight = genv::gout.cascent() + 2*genv::gout.cdescent();
    int _selected;
    int _scrollvalue;
    int _linspace;
    const int _scrollwidth = 20;
    const int _contour = 3;
    Scrollbutton * _scrollbox;
public:
    Listbox(Window *, int, int, int, int, std::string, std::vector<std::string>);

    void draw() override;
    void logic(genv::event&) override;
    int get_height(){return _sizey;}
    int get_linspace(){return _linspace;}
    int get_contour(){return _contour;}
    void change_scrollvalue(int v){_scrollvalue = v;}
    std::string out_value();
    void delete_element(std::string);
    void add_new(std::string s){if(s != "") _items.push_back(s);}

};

#endif // LISTBOX_HPP
