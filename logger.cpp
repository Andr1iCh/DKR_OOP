#include "logger.h"

Logger::Logger(const std::string& path) {
    file.open(path, std::ios::app);
}

void Logger::log(const std::string& msg) {
    if (file.is_open()) {
        file << msg << std::endl;
    }
}

Logger::~Logger() {
    if (file.is_open()) {
        file.close();
    }
}
