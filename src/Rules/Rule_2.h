#include <stddef.h>

#pragma once

template <size_t quantity = 0>
class Rule_2
{
    int number_of_enemies_killed = quantity;

public:
    int get_quantity()
    {
        return number_of_enemies_killed;
    }

    void set_quantity(int enemies_count)
    {
        number_of_enemies_killed = enemies_count;
    }

    bool check(int q)
    {
        return q >= number_of_enemies_killed;
    }
};
