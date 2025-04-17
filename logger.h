#ifndef LOGGER_H
#define LOGGER_H
//#include <fstream>
//#include <string>
#include <QString>
#include <Qfile>
#include <QTextStream>

class Logger {
    //std::ofstream file;
    QFile file;
    QTextStream stream;
public:
    Logger(const QString filename);

    void log(const QString& msg);

    ~Logger();
};


#endif // LOGGER_H
