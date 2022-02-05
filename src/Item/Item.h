#include <string>
#include "../Field/Field.h"

#pragma once

class Item
{
public:
    virtual void generate(Field *field) = 0;
    virtual void set_xy(int i, int j) = 0;
    virtual int get_x() = 0;
    virtual int get_y() = 0;
    virtual bool is_used() = 0;
    virtual int use() = 0;
};
