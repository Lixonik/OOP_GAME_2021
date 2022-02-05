#include "../Enemy/Enemy.h"

#pragma once

class Goblin : public Enemy
{
    int x, y;
    int hp = 60, damage = 40, defense = 15;
    bool life = true;

    Random randomcity;
    Field *board;

public:
    Goblin() = default;
  
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
    
    friend std::ostream &operator<<(std::ostream &out, const Goblin &object);

    friend bool operator==(const Goblin &object_1, const Goblin &object_2);

    friend bool operator!=(const Goblin &object_1, const Goblin &object_2);
        
    Goblin(const Goblin &other);
    Goblin &operator=(const Goblin &other);
};
