#include "Sword.h"

void Sword ::generate(Field *field)
{
    board = field;

    if (board->get_swords_count() > 0)
        for (int i = 1; i < board->get_width() - 1; i++)
            for (int j = 1; j < board->get_height() - 1; j++)
                if (board->get_cell(i, j)->is_item() && !board->get_cell(i, j)->is_item_visit())
                {
                    set_xy(i, j);
                    board->get_cell(i, j)->set_item_visit();
                    board->get_cell(i, j)->set_sword();
                    board->swords_count_decrement();
                    return;
                }
}

void Sword ::set_xy(int i, int j)
{
    x = i;
    y = j;
}

int Sword::get_x()
{
    return x;
}

int Sword::get_y()
{
    return y;
}

bool Sword ::is_used()
{
    return used;
}

int Sword ::use()
{
    used = true;
    board->get_cell(x, y)->set_item(false);
    board->get_cell(x, y)->set_sword(false);

    return 2;
}

std::ostream &operator<<(std::ostream &out, const Sword &object)
{
    out << "sword\tcoordinates: " + std::to_string(object.x) + "," + std::to_string(object.y) + "\tused: " + (object.used ? "YES" : "NO");

    return out;
}

bool operator==(const Sword &object_1, const Sword &object_2)
{
    return (object_1.x == object_2.x && object_1.y == object_2.y && object_1.used == object_2.used);
}

bool operator!=(const Sword &object_1, const Sword &object_2)
{
    return !(object_1 == object_2);
}

Sword::Sword(const Sword &other) : x(other.x), y(other.y), used(other.used) {}

Sword &Sword::operator=(const Sword &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        used = other.used;
    }

    return *this;
}
