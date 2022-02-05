#include <fstream>
#include "../LoggingListener/LoggingListener.h"

#pragma once

class FileLoggingListener : public LoggingListener
{
    std::ofstream out;
public:
    void generate(const std::string &name);
    std::ofstream &get_stream();
    ~FileLoggingListener();
};