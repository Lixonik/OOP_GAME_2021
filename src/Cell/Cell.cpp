#include "Cell.h"

Cell ::Cell(bool passability) : passability(passability) {}

int Cell ::get_x()
{
    return x;
}

int Cell ::get_y()
{
    return y;
}

void Cell ::set_cell(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

void Cell ::set_player(bool value)
{
    player = value;
}

void Cell ::set_passability(bool value)
{
    passability = value;
}

void Cell ::set_enemy(bool value)
{
    enemy = value;
}

void Cell ::set_zombie(bool value)
{
    zombie = value;
}

void Cell ::set_goblin(bool value)
{
    goblin = value;
}

void Cell ::set_orc(bool value)
{
    orc = value;
}

void Cell ::set_item(bool value)
{
    item = value;
}

void Cell ::set_med_kit(bool value)
{
    med_kit = value;
}

void Cell ::set_sword(bool value)
{
    sword = value;
}

void Cell ::set_armor(bool value)
{
    armor = value;
}

void Cell ::set_entrance(bool value)
{
    entrance = value;
}

void Cell ::set_exit(bool value)
{
    exit = value;
}

void Cell ::set_wall(bool value)
{
    passability = value;
}

void Cell ::set_maze_visit(bool value)
{
    maze_visit = value;
}

void Cell ::set_enemy_visit(bool value)
{
    enemy_visit = value;
}

void Cell ::set_item_visit(bool value)
{
    item_visit = value;
}

bool Cell ::is_passability()
{
    return passability;
}

bool Cell ::is_player()
{
    return player;
}

bool Cell ::is_enemy()
{
    return enemy;
}

bool Cell ::is_zombie()
{
    return zombie;
}

bool Cell ::is_goblin()
{
    return goblin;
}

bool Cell ::is_orc()
{
    return orc;
}

bool Cell ::is_item()
{
    return item;
}

bool Cell ::is_med_kit()
{
    return med_kit;
}

bool Cell ::is_sword()
{
    return sword;
}

bool Cell ::is_armor()
{
    return armor;
}

bool Cell ::is_entrance()
{
    return entrance;
}

bool Cell ::is_exit()
{
    return exit;
}

bool Cell ::is_maze_visit()
{
    return maze_visit;
}

bool Cell ::is_enemy_visit()
{
    return enemy_visit;
}

bool Cell ::is_item_visit()
{
    return item_visit;
}

std::ostream &operator<<(std::ostream &out, const Cell &object)
{
    out << "CELL (" << object.x << ',' << object.y << ")"
        << " INFO" << std::endl;
    out << "passability: " << object.passability << std::endl;
    out << "player: " << object.player << std::endl;
    out << "enemy: " << object.enemy << std::endl;
    out << "item: " << object.item << std::endl;
    out << "entrance: " << object.entrance << std::endl;
    out << "exit: " << object.exit;

    return out;
}

bool operator==(const Cell &cell_1, const Cell &cell_2)
{
    return (cell_1.x == cell_2.x && cell_1.y == cell_2.y && cell_1.passability == cell_2.passability && cell_1.player == cell_2.player && cell_1.enemy == cell_2.enemy && cell_1.item == cell_2.item && cell_1.entrance == cell_2.entrance && cell_1.exit == cell_2.exit && cell_1.maze_visit == cell_2.maze_visit && cell_1.enemy_visit == cell_2.enemy_visit && cell_1.item_visit == cell_2.item_visit && cell_1.zombie == cell_2.zombie && cell_1.goblin == cell_2.goblin && cell_1.orc == cell_2.orc && cell_1.med_kit == cell_2.med_kit && cell_1.sword == cell_2.sword && cell_1.armor == cell_2.armor);
}

bool operator!=(const Cell &cell_1, const Cell &cell_2)
{
    return !(cell_1 == cell_2);
}
