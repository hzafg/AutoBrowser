#ifndef LOGGER_H
#define LOGGER_H
#include <string>

using namespace std;
class Logger
{
public:
    static void debug(const string& msg);
    static void info(const string& msg);
    static void warning(const string& msg);
    static void error(const string& msg);
};

#endif // LOGGER_H
