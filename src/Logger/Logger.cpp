#include "Logger.h"

Logger *Logger::instance = nullptr;

Logger ::Logger(Model *model) : state(*model) {}

Logger *Logger ::get_instance(Model *model)
{
    if (instance == nullptr)
        instance = new Logger(model);

    return instance;
}

void Logger ::respond_to_changes(Model *model)
{
    std::time_t time = std::time(0);
    std::tm *now = std::localtime(&time);

    for (LoggingListener *listener : listeners)
    {

        {
            if (state.actor != model->actor)
                listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->actor << std::endl;

            for (int i = 0; i < state.zombies_count; i++)
                if (state.zombies[i] != model->zombies[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->zombies[i] << std::endl;

            for (int i = 0; i < state.goblins_count; i++)
                if (state.goblins[i] != model->goblins[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->goblins[i] << std::endl;

            for (int i = 0; i < state.orcs_count; i++)
                if (state.orcs[i] != model->orcs[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->orcs[i] << std::endl;

            for (int i = 0; i < state.med_kits_count; i++)
                if (state.med_kits[i] != model->med_kits[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->med_kits[i] << std::endl;

            for (int i = 0; i < state.swords_count; i++)
                if (state.swords[i] != model->swords[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->swords[i] << std::endl;

            for (int i = 0; i < state.armor_count; i++)
                if (state.armor[i] != model->armor[i])
                    listener->get_stream() << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << now->tm_mday << "\t" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\t" << model->armor[i] << std::endl;
        }
    }

    state = *model;
}

void Logger ::subscribe(LoggingListener &listener)
{
    listeners.push_back(&listener);
}

void Logger ::unsubscribe(LoggingListener &listener)
{
    for (int i = 0; i < listeners.size(); i++)
        if (listeners[i] == &listener)
        {
            listeners.erase(listeners.begin() + i);

            return;
        }
}

Logger ::~Logger()
{
    if (instance)
        delete instance;
}