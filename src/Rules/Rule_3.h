#include <stddef.h>

#pragma once

template <size_t quantity = 0>
class Rule_3
{
    int used_items = quantity;

public:
    int get_quantity()
    {
        return used_items;
    }

    void set_quantity(int items_count)
    {
        used_items = items_count;
    }

    bool check(int q)
    {
        return q >= used_items;
    }
};