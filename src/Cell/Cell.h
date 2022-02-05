#include "ICell.h"

#pragma once

class Cell : public ICell
{
    int x, y;
    bool passability;                                
    bool player = false, enemy = false, item = false;
    bool zombie = false, goblin = false, orc = false;
    bool med_kit = false, sword = false, armor = false; 
    bool maze_visit = false, enemy_visit = false, item_visit = false;     
    bool entrance = false, exit = false;              

public:
    Cell(bool passability = true);

    int get_x();
    int get_y();

    void set_cell(int new_x, int new_y);

    void set_passability(bool value = true);

    void set_player(bool value = true);

    void set_enemy(bool value = true);

    void set_zombie(bool value = true);

    void set_goblin(bool value = true);

    void set_orc(bool value = true);

    void set_item(bool value = true);

    void set_med_kit(bool value = true);

    void set_sword(bool value = true);
    
    void set_armor(bool value = true);

    void set_entrance(bool value = true);

    void set_exit(bool value = true);

    void set_wall(bool value = false);

    void set_maze_visit(bool value = true);

    void set_enemy_visit(bool value = true);

    void set_item_visit(bool value = true);

    bool is_passability();

    bool is_player();

    bool is_enemy();
  
    bool is_zombie();

    bool is_goblin();

    bool is_orc();
     
    bool is_item();
   
    bool is_med_kit();

    bool is_sword();

    bool is_armor();
     
    bool is_entrance();

    bool is_exit();

    bool is_maze_visit();

    bool is_enemy_visit();

    bool is_item_visit();

    friend std::ostream &operator<<(std::ostream &out, const Cell &object);

    friend bool operator==(const Cell &cell_1, const Cell &cell_2);

    friend bool operator!=(const Cell &cell_1, const Cell &cell_2);
};
