#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "termctrl.h"

class MenuItem {
public:
    MenuItem(int s);
    int switch_to();
    virtual void increment();
    virtual void decrement();
    virtual int confirm();
    virtual std::string get_string();
    virtual std::string get_string_hover();
    virtual int length();
    virtual int center();
private:
    int _switch_to;
};

class MenuButton : public MenuItem {
public:
    MenuButton(std::string t, int s);
    virtual std::string get_string();
    virtual std::string get_string_hover();
    int length();
    int center();
private:
    std::string _label;
    int _switch_to;
    int _length;
    int _center;
};

class MenuInt : public MenuItem {
public:
    MenuInt(std::string l, int flo, int ceil, int def, int s);
    virtual std::string get_string();
    virtual std::string get_string_hover();
    void increment();
    void decrement();
    int get_value();
    int length();
    int center();
private:
    std::string _label;
    int _floor;
    int _ceiling;
    int _value;
    int _slots;
    int _switch_to;
    int _length;
    int _center;
};

class Menu {
public:
    Menu(int s, int w, int h, int x, int y);
    int width();
    int height();
    int x();
    int y();
    void set_title(std::string t);
    void add_button(std::string l, int s);
    void add_int(std::string l, int f, int c, int d, int s);
    void draw_title();
    void draw_item(int idx);
    void draw_current();
    void draw_all();
    int parse_input(int input);
private:
    void move_up();
    void move_down();
    void increment();
    void decrement();
    int confirm();
    std::pair<int, int> find_rc(int idx);
    int _own_state;
    int _width;
    int _height;
    int _x;
    int _y;
    int _center_x;
    std::string _title;
    int _title_center;
    std::vector<std::shared_ptr<MenuItem>> _items;
    int _ptr;
    const int _TITLE_OFF = 2;
    const int _ITEM_OFF = 5;
};