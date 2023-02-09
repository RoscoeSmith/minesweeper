#include "Menu.h"

// Dummy Parent Class
MenuItem::MenuItem(int s) : _switch_to(s) { }

int MenuItem::switch_to() {
    return _switch_to;
}

int MenuItem::confirm() {
    return switch_to();
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
MenuButton::MenuButton(std::string t, int s) : MenuItem(s), _label(t) {
    _length = _label.size() + 2;
    _center = _length / 2;
}

std::string MenuButton::get_string() {
    return std::string(" " + _label + " ");
}

std::string MenuButton::get_string_hover() {
    return std::string("\e[37m[\e[0m" + _label + "\e[37m]\e[0m");
}

int MenuButton::length() {
    return _length;
}

int MenuButton::center() {
    return _center;
}

// Menu
Menu::Menu(int s, int w, int h, int x, int y) : _own_state(s), _width(w), _height(h), _x(x), _y(y) {
    _ptr = 0;
    _center_x = _width / 2;
}

void Menu::set_title(std::string t) {
    _title = t;
}

void Menu::add_button(std::string l, int s = -1) {
    if (s == -1) {
        s = _own_state;
    }
    _items.push_back(std::make_shared<MenuButton>(l, s));
}

void Menu::draw_title() {
    return;
}

void Menu::draw_item(int idx) {
    std::string out;
    if (idx == _ptr) {
        out = _items[idx]->get_string_hover();
    } else {
        out = _items[idx]->get_string();
    }
    std::pair<int, int> cpos = find_rc(idx);
    print_at(cpos.first, cpos.second, out);
}

void Menu::draw_current() {
    draw_item(_ptr);
}

int Menu::parse_input(int input) {
    switch (input) {
        case Input::UP:
            move_up();
            break;
        case Input::DOWN:
            move_down();
            break;
        case Input::CONFIRM:
            return confirm();
        case Input::QUIT:
            return 1; // Exit state
        case Input::UNKNOWN:
            break;
        default:
            break;
    }
    return _own_state;
}

void Menu::move_up() {
    int last = _ptr;
    _ptr = std::max(0, _ptr - 1);
    if (last != _ptr) {
        draw_current();
        draw_item(last);
    }
}

void Menu::move_down() {
    int last = _ptr;
    _ptr = std::min(_ptr + 1, (int) _items.size() - 1);
    if (last != _ptr) {
        draw_current();
        draw_item(last);
    }
}

int Menu::confirm() {
    return _items[_ptr]->confirm();
}

std::pair<int, int> Menu::find_rc(int idx) {
    return std::make_pair<int, int>(_ITEM_OFF + (2 * idx), _x + _center_x - _items[idx]->center());
}