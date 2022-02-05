#include "../Item/Item.h"

#pragma once

class Armor : public Item
{
    int x, y;
    bool used = false;

    Field *board;

public:
    Armor() = default;
  
    void generate(Field *field);
    void set_xy(int i, int j);
    int get_x();
    int get_y();
    bool is_used();
    int use();
        
    friend std::ostream &operator<<(std::ostream &out, const Armor &object);

    friend bool operator==(const Armor &object_1, const Armor &object_2);

    friend bool operator!=(const Armor &object_1, const Armor &object_2);
            
    Armor(const Armor &other);
    Armor &operator=(const Armor &other);
};
