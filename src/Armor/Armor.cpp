#include "Armor.h"

void Armor ::generate(Field *field)
{
    board = field;

    if (board->get_armor_count() > 0)
        for (int i = 1; i < board->get_width() - 1; i++)
            for (int j = 1; j < board->get_height() - 1; j++)
                if (board->get_cell(i, j)->is_item() && !board->get_cell(i, j)->is_item_visit())
                {
                    set_xy(i, j);
                    board->get_cell(i, j)->set_item_visit();
                    board->get_cell(i, j)->set_armor();
                    board->armor_count_decrement();
                    return;
                }
}

void Armor ::set_xy(int i, int j)
{
    x = i;
    y = j;
}

int Armor::get_x()
{
    return x;
}

int Armor::get_y()
{
    return y;
}

bool Armor ::is_used()
{
    return used;
}

int Armor ::use()
{
    used = true;
    board->get_cell(x, y)->set_item(false);
    board->get_cell(x, y)->set_armor(false);

    return 3;
}

std::ostream &operator<<(std::ostream &out, const Armor &object)
{
    out << "med kit\tcoordinates: " + std::to_string(object.x) + "," + std::to_string(object.y) + "\tused: " + (object.used ? "YES" : "NO");

    return out;
}

bool operator==(const Armor &object_1, const Armor &object_2)
{
    return (object_1.x == object_2.x && object_1.y == object_2.y && object_1.used == object_2.used);
}

bool operator!=(const Armor &object_1, const Armor &object_2)
{
    return !(object_1 == object_2);
}

Armor::Armor(const Armor &other) : x(other.x), y(other.y), used(other.used) {}

Armor &Armor::operator=(const Armor &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        used = other.used;
    }

    return *this;
}
