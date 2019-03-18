#include "logger.h"
#include <iostream>

void Logger::debug(const string &msg)
{
    cout << msg << endl;
}

void Logger::info(const string &msg)
{
    cout << msg << endl;
}

void Logger::warning(const string &msg)
{
    cout << msg << endl;
}

void Logger::error(const string &msg)
{
    cout << msg << endl;
}
