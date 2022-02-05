#include "Player.h"

Player::Player(int hp, int damage, int defense, int collisions) : hp(hp), damage(damage), defense(defense), collisions(collisions) 
{
    if (hp < 1 || hp > 200 || damage < 50 || defense < 5 || collisions < 0)
        throw "The save file is not correct";
} 

void Player::generate(Field *field)
{
    board = field;

    for (int i = 1; i < board->get_width() - 1; i++)
        for (int j = 1; j < board->get_height() - 1; j++)
            if (board->get_cell(i, j)->is_player())
                set_xy(i, j);
}

void Player ::set_xy(int i, int j)
{
    x = i;
    y = j;
}

int Player ::get_x()
{
    return x;
}

int Player ::get_y()
{
    return y;
}

int Player ::get_hp()
{
    return hp;
}

int Player ::get_damage()
{
    return damage;
}

int Player ::get_defense()
{
    return defense;
}

int Player ::get_collisions()
{
    return collisions;
}

void Player ::move_up_x()
{
    if (board->get_cell(x + 1, y)->is_passability() && !board->get_cell(x + 1, y)->is_enemy())
    {
        board->get_cell(x, y)->set_player(false);
        x++;
        board->get_cell(x, y)->set_player();
    }
    else if (!board->get_cell(x + 1, y)->is_passability())
        collisions++;
    
}

void Player ::move_back_x()
{
    if (board->get_cell(x - 1, y)->is_passability() && !board->get_cell(x - 1, y)->is_enemy())
    {
        board->get_cell(x, y)->set_player(false);
        x--;
        board->get_cell(x, y)->set_player();
    }
    else if (!board->get_cell(x - 1, y)->is_passability())
        collisions++;
}

void Player ::move_up_y()
{
    if (board->get_cell(x, y + 1)->is_passability() && !board->get_cell(x, y + 1)->is_enemy())
    {
        board->get_cell(x, y)->set_player(false);
        y++;
        board->get_cell(x, y)->set_player();
    }
    else if (!board->get_cell(x, y + 1)->is_passability())
        collisions++;
}

void Player ::move_back_y()
{
    if (board->get_cell(x, y - 1)->is_passability() && !board->get_cell(x, y - 1)->is_enemy())
    {
        board->get_cell(x, y)->set_player(false);
        y--;
        board->get_cell(x, y)->set_player();
    }
    else if (!board->get_cell(x, y - 1)->is_passability())
        collisions++;
}

void Player ::item_interaction(Item &item)
{
    if (!item.is_used())
    {
        int option = item.use();
        switch (option)
        {
        case 1: // med kit
            hp = 200;
            break;
        case 2: // sword
            damage += 15;
            break;
        case 3: // armor
            defense += 10;
            break;
        }
    }
}

bool Player ::battle(Enemy &enemy)
{
    while (enemy.get_hp() > 0 && hp > 0)
    {
        enemy.take_damage(damage);
        if (enemy.get_hp() > 0)
            if (enemy.get_damage() > defense)
                hp -= enemy.get_damage() - defense;
    }

    if (hp > 0)
    {
        enemy.destroy();
        return true;
    }
    else
        return false;
}

std::ostream &operator<<(std::ostream &out, const Player &object)
{
    out << "player\tcoordinates: " + std::to_string(object.x) + "," + std::to_string(object.y) + "\thp: " + std::to_string(object.hp) + " / 200\t" + "defense: " + std::to_string(object.defense) + "\tdamage: " + std::to_string(object.damage);

    return out;
}

bool operator==(const Player &object_1, const Player &object_2)
{
    return (object_1.x == object_2.x && object_1.y == object_2.y && object_1.hp == object_2.hp && object_1.defense == object_2.defense && object_1.damage == object_2.damage);
}

bool operator!=(const Player &object_1, const Player &object_2)
{
    return !(object_1 == object_2);
}

Player::Player(const Player &other) : x(other.x), y(other.y), hp(other.hp), damage(other.damage), defense(other.defense), collisions(other.collisions) {}

Player &Player::operator=(const Player &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        hp = other.hp;
        damage = other.damage;
        defense = other.defense;
        collisions = other.collisions;
    }

    return *this;
}
