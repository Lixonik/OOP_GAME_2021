#pragma once

enum Direction
{
    Down    = 'S',
    Left    = 'A',
    Right   = 'D',
    Up      = 'W',
    Save    = 'O',
    Load    = 'P'
};

class Button
{
public:
    virtual int execute(int command) = 0;
};