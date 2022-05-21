#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "widget.hpp"
#include "button.hpp"

#include <string>

class Textbox : public Widget {
protected:
    std::string _text;
    int _cursor;
    FButton* _fbutton;
    const int _textborder = 4;
public:
    Textbox(Window *, int, int, int, int, std::string, FButton*);
    void draw() const override;
    void logic(genv::event&) override;
    void add_text(std::string t);
    void remove_text();
    bool move_cursor(genv::event&);
    void check_cursor();
    std::string get_text() {return _text;}
    void clear_text(){_text = ""; _cursor = 0;}
};

#endif // TEXTBOX_HPP_INCLUDED
