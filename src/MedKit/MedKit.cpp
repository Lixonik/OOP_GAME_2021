#include "MedKit.h"

void MedKit ::generate(Field *field)
{
    board = field;

    if (board->get_med_kits_count() > 0)
        for (int i = 1; i < board->get_width() - 1; i++)
            for (int j = 1; j < board->get_height() - 1; j++)
                if (board->get_cell(i, j)->is_item() && !board->get_cell(i, j)->is_item_visit())
                {
                    set_xy(i, j);
                    board->get_cell(i, j)->set_item_visit();
                    board->get_cell(i, j)->set_med_kit();
                    board->med_kits_count_decrement();
                    return;
                }
}

void MedKit ::set_xy(int i, int j)
{
    x = i;
    y = j;
}

int MedKit::get_x()
{
    return x;
}

int MedKit::get_y()
{
    return y;
}

bool MedKit ::is_used()
{
    return used;
}

int MedKit ::use()
{
    used = true;
    board->get_cell(x, y)->set_item(false);
    board->get_cell(x, y)->set_med_kit(false);

    return 1;
}

std::ostream &operator<<(std::ostream &out, const MedKit &object)
{
    out << "med kit\tcoordinates: " + std::to_string(object.x) + "," + std::to_string(object.y) + "\tused: " + (object.used ? "YES" : "NO");

    return out;
}

bool operator==(const MedKit &object_1, const MedKit &object_2)
{
    return (object_1.x == object_2.x && object_1.y == object_2.y && object_1.used == object_2.used);
}

bool operator!=(const MedKit &object_1, const MedKit &object_2)
{
    return !(object_1 == object_2);
}

MedKit::MedKit(const MedKit &other) : x(other.x), y(other.y), used(other.used) {}

MedKit &MedKit::operator=(const MedKit &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        used = other.used;
    }

    return *this;
}
