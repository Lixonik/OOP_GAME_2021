#include "../Item/Item.h"

#pragma once

class MedKit : public Item
{
    int x, y;
    bool used = false;

    Field *board;

public:
    MedKit() = default;
  
    void generate(Field *board);
    void set_xy(int i, int j);
    int get_x();
    int get_y();
    bool is_used();
    int use();
    
    friend std::ostream &operator<<(std::ostream &out, const MedKit &object);

    friend bool operator==(const MedKit &object_1, const MedKit &object_2);

    friend bool operator!=(const MedKit &object_1, const MedKit &object_2);
    
    MedKit(const MedKit &other);
    MedKit &operator=(const MedKit &other);
};
