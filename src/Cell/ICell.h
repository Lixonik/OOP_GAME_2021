#include <iostream>

#pragma once

class ICell
{
public:
    virtual int get_x() = 0;
    virtual int get_y() = 0;
    virtual void set_cell(int new_x, int new_y) = 0;
    virtual void set_passability(bool value = true) = 0;
    virtual void set_player(bool value = true) = 0;
    virtual void set_enemy(bool value = true) = 0;
    virtual void set_zombie(bool value = true) = 0;
    virtual void set_goblin(bool value = true) = 0;
    virtual void set_orc(bool value = true) = 0; 
    virtual void set_item(bool value = true) = 0;
    virtual void set_med_kit(bool value = true) = 0;
    virtual void set_sword(bool value = true) = 0;
    virtual void set_armor(bool value = true) = 0;
    virtual void set_entrance(bool value = true) = 0;
    virtual void set_exit(bool value = true) = 0;
    virtual void set_wall(bool value = false) = 0;
    virtual void set_maze_visit(bool value = true) = 0;
    virtual void set_enemy_visit(bool value = true) = 0;
    virtual void set_item_visit(bool value = true) = 0;
    virtual bool is_passability() = 0;
    virtual bool is_player() = 0;
    virtual bool is_enemy() = 0; 
    virtual bool is_zombie() = 0;
    virtual bool is_goblin() = 0;
    virtual bool is_orc() = 0;
    virtual bool is_item() = 0;
    virtual bool is_med_kit() = 0;
    virtual bool is_sword() = 0;
    virtual bool is_armor() = 0;
    virtual bool is_entrance() = 0;
    virtual bool is_exit() = 0;
    virtual bool is_maze_visit() = 0;
    virtual bool is_enemy_visit() = 0;
    virtual bool is_item_visit() = 0;
};
