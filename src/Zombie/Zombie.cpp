#include "Zombie.h"

void Zombie::generate(Field *field)
{
    board = field;

    if (board->get_zombies_count() > 0)
        for (int i = 1; i < board->get_width() - 1; i++)
            for (int j = 1; j < board->get_height() - 1; j++)
                if (board->get_cell(i, j)->is_enemy() && !board->get_cell(i, j)->is_enemy_visit())
                {
                    set_xy(i, j);
                    board->get_cell(i, j)->set_enemy_visit();
                    board->get_cell(i, j)->set_zombie();
                    board->zombies_count_decrement();
                    return;
                }
}

void Zombie::set_xy(int i, int j)
{
    x = i;
    y = j;
}



int Zombie::get_x()
{
    return x;
}

int Zombie::get_y()
{
    return y;
}

void Zombie::move()
{
    int option = randomcity.generate(0, 3);

    if (life)
        switch (option)
        {
        case 0:
            if (board->get_cell(x, y + 1)->is_passability() && !board->get_cell(x, y + 1)->is_entrance() && !board->get_cell(x, y + 1)->is_exit() && !board->get_cell(x, y + 1)->is_player() && !board->get_cell(x, y + 1)->is_item())
            {
                board->get_cell(x, y)->set_passability();
                board->get_cell(x, y)->set_zombie(false);
                board->get_cell(x, y)->set_enemy(false);
                y++;
                board->get_cell(x, y)->set_enemy();
                board->get_cell(x, y)->set_zombie();
                board->get_cell(x, y)->set_passability(false);

                return;
            }
            break;

        case 1:
            if (board->get_cell(x, y - 1)->is_passability() && !board->get_cell(x, y - 1)->is_entrance() && !board->get_cell(x, y - 1)->is_exit() && !board->get_cell(x, y - 1)->is_player() && !board->get_cell(x, y - 1)->is_item())
            {
                board->get_cell(x, y)->set_passability();
                board->get_cell(x, y)->set_zombie(false);
                board->get_cell(x, y)->set_enemy(false);
                y--;
                board->get_cell(x, y)->set_enemy();
                board->get_cell(x, y)->set_zombie();
                board->get_cell(x, y)->set_passability(false);

                return;
            }
            break;

        case 2:
            if (board->get_cell(x - 1, y)->is_passability() && !board->get_cell(x - 1, y)->is_entrance() && !board->get_cell(x - 1, y)->is_exit() && !board->get_cell(x - 1, y)->is_player() && !board->get_cell(x - 1, y)->is_item())
            {
                board->get_cell(x, y)->set_passability();
                board->get_cell(x, y)->set_zombie(false);
                board->get_cell(x, y)->set_enemy(false);
                x--;
                board->get_cell(x, y)->set_enemy();
                board->get_cell(x, y)->set_zombie();
                board->get_cell(x, y)->set_passability(false);

                return;
            }
            break;

        case 3:
            if (board->get_cell(x + 1, y)->is_passability() && !board->get_cell(x + 1, y)->is_entrance() && !board->get_cell(x + 1, y)->is_exit() && !board->get_cell(x + 1, y)->is_player() && !board->get_cell(x + 1, y)->is_item())
            {
                board->get_cell(x, y)->set_passability();
                board->get_cell(x, y)->set_zombie(false);
                board->get_cell(x, y)->set_enemy(false);
                x++;
                board->get_cell(x, y)->set_enemy();
                board->get_cell(x, y)->set_zombie();
                board->get_cell(x, y)->set_passability(false);

                return;
            }
            break;
        }
}

int Zombie ::get_hp()
{
    return hp;
}

void Zombie ::take_damage(int quantity)
{
    if (quantity > defense)
        hp -= quantity - defense;
}

int Zombie ::get_damage()
{
    return damage;
}

void Zombie ::destroy()
{
    board->get_cell(x, y)->set_passability();
    board->get_cell(x, y)->set_enemy(false);
    board->get_cell(x, y)->set_zombie(false);
    life = false;
}

bool Zombie ::is_life()
{
    return life;
}

std::ostream &operator<<(std::ostream &out, const Zombie &object)
{
    out << "zombie\tcoordinates: " + std::to_string(object.x) + "," + std::to_string(object.y) + "\tis life: " + (object.life ? "YES" : "NO");

    return out;
}

bool operator==(const Zombie &object_1, const Zombie &object_2)
{
    return (object_1.x == object_2.x && object_1.y == object_2.y && object_1.hp == object_2.hp && object_1.defense == object_2.defense && object_1.damage == object_2.damage && object_1.life == object_2.life);
}

bool operator!=(const Zombie &object_1, const Zombie &object_2)
{
    return !(object_1 == object_2);
}

Zombie::Zombie(const Zombie &other) : x(other.x), y(other.y), life(other.life) {}

Zombie &Zombie::operator=(const Zombie &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        life = other.life;
    }

    return *this;
}
