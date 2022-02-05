#include "../Field/Field.h"
#include "../Item/Item.h"
#include "../Enemy/Enemy.h"

#pragma once

class Player
{
    int x, y;
    int hp = 200, damage = 50, defense = 5;
    
    int collisions = 0;

    Field *board;

public:
    Player() = default;
    Player(int hp, int damage, int defense, int collisions);
  
    void generate(Field *field);
    void set_xy(int i, int j);
    int get_x();
    int get_y();
    int get_hp();
    int get_damage();
    int get_defense();
    int get_collisions();
    void move_up_x();
    void move_back_x();
    void move_up_y();
    void move_back_y();
    void item_interaction(Item &item);
    bool battle(Enemy &enemy);

    friend std::ostream &operator<<(std::ostream &out, const Player &object);

    friend bool operator==(const Player &object_1, const Player &object_2);

    friend bool operator!=(const Player &object_1, const Player &object_2);

    Player(const Player &other);
    Player &operator=(const Player &other);
};
