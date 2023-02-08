#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "termctrl.h"

class MenuItem {
public:
    virtual void action(int input);
    virtual std::string get_string();
    virtual std::string get_string_hover();
    virtual int length();
    virtual int center();
};

class MenuButton : public MenuItem {
public:
    MenuButton(std::string t);
    virtual void action(int input);
    virtual std::string get_string();
    virtual std::string get_string_hover();
    int length();
    int center();
private:
    std::string _label;
    int _length;
    int _center;
};

class Menu {
public:
    Menu(int w, int h, int x, int y);
    int width();
    int height();
    int x();
    int y();
    void set_title(std::string t);
    void add_button(std::string l);
    void draw_item(int idx);
    void draw_current();
    void draw_all();
private:
    void move_up();
    void move_down();
    std::pair<int, int> find_rc(int idx);
    int _width;
    int _height;
    int _x;
    int _y;
    int _center_x;
    std::string _title;
    std::vector<std::shared_ptr<MenuItem>> _items;
    int _ptr;
    const int _TITLE_OFF = 1;
    const int _ITEM_OFF = 4;
};