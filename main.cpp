#include "mainwindow.h"

#include "logger.h"
#include "customer.h"
#include "customers.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    qDebug() << "ddd";
    Logger logger("log.txt");
    Customers allCustomers(logger);
    std::string path = "customers_encrypted.aes";

    allCustomers.createCustomer("Andrii","C", 4441, 42213, 99999999, logger);
    allCustomers.createCustomer("Roma","C", 1223, 31232, 13211223, logger);
    allCustomers.createCustomer("Olex","C", 2334, 13223, 244444, logger);
    allCustomers.createCustomer("Dmitro","C", 3344, 45422, 12, logger);
    allCustomers.createCustomer("Stepan","C", 3344, 12434, 41223, logger);
    qDebug() << allCustomers.getAllCustomersInfo();

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "DKR_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
