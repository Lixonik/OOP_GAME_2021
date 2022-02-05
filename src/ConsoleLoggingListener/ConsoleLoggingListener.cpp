#include "ConsoleLoggingListener.h"

std::ostream &ConsoleLoggingListener::get_stream()
{
    return std::cout;
}