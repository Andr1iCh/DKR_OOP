#include "logger.h"
//#include <filesystem>
#include <QDir>

Logger::Logger(const QString filename) {
    QDir().mkdir("temp");

    file.setFileName("temp/" + filename);
    if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
    {
        stream.setDevice(&file);
    }
    //std::filesystem::create_directory("temp");
    //file.open("temp/" + path, std::ios::app);
}

void Logger::log(const QString& msg) {
    if (file.isOpen()) {
        QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        stream << "[" << timeStamp << "] " << msg << '\n';
        stream.flush();
    }
}

Logger::~Logger() {
    if (file.isOpen()) {
        file.close();
    }
}
