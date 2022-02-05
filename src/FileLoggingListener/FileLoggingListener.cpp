#include "FileLoggingListener.h"

void FileLoggingListener::generate(const std::string &filename)
{
    out.open(filename);
    if (!out.is_open())
        throw std::runtime_error("file open failure");
}


std::ofstream &FileLoggingListener::get_stream()
{
    return out;
}

FileLoggingListener::~FileLoggingListener()
{
    if (out.is_open())
        out.close();
}
