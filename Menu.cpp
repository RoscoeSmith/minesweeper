#include "Menu.h"

// Dummy Parent Class
void MenuItem::action(int input) {
    return;
}

std::string MenuItem::get_string() {
    return std::string("");
}

std::string MenuItem::get_string_hover() {
    return std::string("");
}

int MenuItem::length() {
    return 0;
}

int MenuItem::center() {
    return 0;
}

// Button
MenuButton::MenuButton(std::string t) : _label(t) {
    _length = _label.size() + 2;
    _center = _length / 2;
}

void MenuButton::action(int input) {
    return;
}

std::string MenuButton::get_string() {
    return std::string(" " + _label + " ");
}

std::string MenuButton::get_string_hover() {
    return std::string("\e[39m[\e[0m" + _label + "\e[39m]\e[0m");
}

int MenuButton::length() {
    return _length;
}

int MenuButton::center() {
    return _center;
}

// Menu
Menu::Menu(int w, int h, int x, int y) : _width(x), _height(h), _x(x), _y(y) {
    _ptr = 0;
    _center_x = _width / 2;
}

void Menu::set_title(std::string t) {
    _title = t;
}

void Menu::add_button(std::string l) {
    _items.push_back(std::make_shared<MenuButton>(l));
}

void Menu::draw_item(int idx) {
    std::string out;
    if (idx == _ptr) {
        out = _items[idx]->get_string_hover();
    } else {
        out = _items[idx]->get_string();
    }
    std::pair<int, int> cpos = find_rc(idx);
    int r = cpos.first;
    int c = cpos.second;
    std::cout << "\e[" << std::to_string(r) << ";" << std::to_string(c) << "H" << out << std::flush;
}

void Menu::draw_current() {
    draw_item(_ptr);
}

void Menu::move_up() {
    _ptr = std::max(0, _ptr - 1);
}

void Menu::move_down() {
    _ptr = std::min(_ptr + 1, (int) _items.size());
}

std::pair<int, int> Menu::find_rc(int idx) {
    return std::make_pair<int, int>(_ITEM_OFF + (2 * idx), _x + _center_x - _items[idx]->center());
}