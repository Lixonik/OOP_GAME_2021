#include <vector>
#include <ctime>
#include "../LoggingListener/LoggingListener.h"
#include "../Model/Model.h"

#pragma once

class Logger
{
    static Logger *instance;
    Model state;
    std::vector<LoggingListener *> listeners;

    Logger(Model *model);
public:
    static Logger *get_instance(Model *model);

    Logger(Logger &other) = delete;

    void operator=(const Logger &) = delete;

    void respond_to_changes(Model *model);

    void subscribe(LoggingListener &listener);

    void unsubscribe(LoggingListener &listener);

    ~Logger();
};