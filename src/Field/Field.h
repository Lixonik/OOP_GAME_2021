#include <vector>
#include "../Cell/Cell.h"
#include "../Random/Random.h"

#pragma once

class Field
{
    int width, height;
    Cell **arr_cell;
    int zombies_count = 0, goblins_count = 0, orcs_count = 0;
    int med_kits_count = 0, swords_count = 0, armor_count = 0;
    int x_exit, y_exit;

    Random randomcity;

    void destroy();

    void walling();

    void maze_generating();

    void dfs(Cell **grid, int i, int j);

    void delete_deadblocks(int i, int j);

    void construct_entrance_exit();

    void enemies_spawning();

    void items_spawning();

    void player_spawning();

public:
    Field();

    Field(std::vector<std::string> map, int width, int height);

    Field(const Field &other);

    Field(Field &&other);

    Field &operator=(const Field &other);

    Field &operator=(Field &&other);

    friend std::ostream &operator<<(std::ostream &out, const Field &object);

    friend bool operator==(const Field &field_1, const Field &field_2);

    friend bool operator!=(const Field &field_1, const Field &field_2);

    int get_width();

    int get_height();

    Cell *get_cell(int x, int y);

    int get_x_exit();

    int get_y_exit();

    int get_zombies_count();

    void zombies_count_decrement();

    int get_goblins_count();

    void goblins_count_decrement();

    int get_orcs_count();

    void orcs_count_decrement();

    int get_med_kits_count();

    void med_kits_count_decrement();

    int get_swords_count();

    void swords_count_decrement();

    int get_armor_count();

    void armor_count_decrement();

    ~Field();
};
