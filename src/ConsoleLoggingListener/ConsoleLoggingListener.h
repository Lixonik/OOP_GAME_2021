#include "../LoggingListener/LoggingListener.h"

#pragma once

class ConsoleLoggingListener : public LoggingListener
{
public:
    std::ostream &get_stream();
};