#include "View.h"

View *View::instance = nullptr;

View *View ::get_instance()
{
    if (instance == nullptr)
        instance = new View;

    return instance;
}

void View::set_color(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void View::imagine(std::string info, ConsoleColor text, ConsoleColor background)
{
    set_color(text, background);
    std::cout << info;
    set_color(White, Black);
}

void View::err(std::string info)
{
    std::cerr << info << std::endl;
}

void View::pause()
{
    system("pause");
}

void View::clear()
{
    system("cls");
}

View ::~View()
{
    if (instance)
        delete instance;
}