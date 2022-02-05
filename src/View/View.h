#include <iostream>
#include <windows.h>
#include <string>

#pragma once

enum ConsoleColor
{
    Black           = 0,
    Blue            = 1,
    Green           = 2,
    Cyan            = 3,
    Red             = 4,
    Magenta         = 5,
    Brown           = 6,
    LightGray       = 7,
    DarkGray        = 8,
    LightBlue       = 9,
    LightGreen      = 10,
    LightCyan       = 11,
    LightRed        = 12,
    LightMagenta    = 13,
    Yellow          = 14,
    White           = 15
};

class View
{
    static View *instance;

    void set_color(ConsoleColor text, ConsoleColor background);
    View() = default;
public:
    static View *get_instance();
    View(View &other) = delete;
    void operator=(const View &) = delete;
    virtual void imagine(std::string info, ConsoleColor text = White, ConsoleColor background = Black);
    virtual void err(std::string info);
    virtual void pause();
    virtual void clear();
    ~View();
};

