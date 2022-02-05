#include "../Enemy/Enemy.h"

#pragma once

class Zombie : public Enemy
{
    int x, y;
    int hp = 120, damage = 30, defense = 10;
    bool life = true;

    Random randomcity;
    Field *board;

public:
    Zombie() = default;

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

    friend std::ostream &operator<<(std::ostream &out, const Zombie &object);

    friend bool operator==(const Zombie &object_1, const Zombie &object_2);

    friend bool operator!=(const Zombie &object_1, const Zombie &object_2);

    Zombie(const Zombie &other);
    Zombie &operator=(const Zombie &other);
};
