#include "../Item/Item.h"

#pragma once

class Sword : public Item
{
    int x, y;
    bool used = false;

    Field *board;

public:
    Sword() = default;
    
    void generate(Field *field);
    void set_xy(int i, int j);
    int get_x();
    int get_y();
    bool is_used();
    int use();
    
    friend std::ostream &operator<<(std::ostream &out, const Sword &object);

    friend bool operator==(const Sword &object_1, const Sword &object_2);

    friend bool operator!=(const Sword &object_1, const Sword &object_2);
        
    Sword(const Sword &other);
    Sword &operator=(const Sword &other);
};
