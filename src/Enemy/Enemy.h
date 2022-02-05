#include <string>
#include "../Field/Field.h"
#include "../Random/Random.h"

#pragma once

class Enemy
{
public:
    virtual void generate(Field *field) = 0;
    virtual void set_xy(int i, int j) = 0;
    virtual int get_x() = 0;
    virtual int get_y() = 0;
    virtual void move() = 0;
    virtual int get_hp() = 0;
    virtual void take_damage(int quantity) = 0;
    virtual int get_damage() = 0;
    virtual void destroy() = 0;
    virtual bool is_life() = 0;
};
