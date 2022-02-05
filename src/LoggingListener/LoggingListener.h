#include <iostream>
#include <string>

#pragma once

class LoggingListener
{
public:
    virtual std::ostream &get_stream() = 0;
};