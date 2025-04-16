#include "logger.h"
#include <filesystem>

Logger::Logger(const std::string& path) {
    std::filesystem::create_directory("temp");
    file.open("temp/" + path, std::ios::app);
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
