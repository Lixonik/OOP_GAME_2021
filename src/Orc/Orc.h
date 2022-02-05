#include "../Enemy/Enemy.h"

#pragma once

class Orc : public Enemy
{
    int x, y;
    int hp = 80, damage = 50, defense = 0;
    bool life = true;

    Random randomcity;
    Field *board;

public:
    Orc() = default;
  
    void generate(Field *field);
    void set_xy(int i, int j);
    int get_x();
    int get_y();
    void move();
    int get_hp();
    void take_damage(int quantity);
    int get_damage();
    void destroy();
    bool is_life();

    friend std::ostream &operator<<(std::ostream &out, const Orc &object);

    friend bool operator==(const Orc &object_1, const Orc &object_2);

    friend bool operator!=(const Orc &object_1, const Orc &object_2);
    
    Orc(const Orc &other);
    Orc &operator=(const Orc &other);
};
