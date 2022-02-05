#include <stddef.h>
#pragma once

template <size_t quantity = 5>
class Rule_1
{
    int collisions = quantity;

public:
    bool check(int q)
    {
        return q < collisions;
    }
};
