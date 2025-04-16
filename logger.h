#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <string>
class Logger {
    std::ofstream file;
public:
    Logger(const std::string& path);

    void log(const std::string& msg);

    ~Logger();
};


#endif // LOGGER_H
