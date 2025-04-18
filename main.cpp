#include "mainwindow.h"

#include "logger.h"
#include "customer.h"
#include "customers.h"
#include "sorter.h"
#include "searcher.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    Logger logger("test_log.txt");
    Customers group(logger);
    group.createCustomer("John", "Smith", 1111, 2222, 500.50, logger);   // ID 1
    group.createCustomer("Alice", "Brown", 3333, 4444, 1000.00, logger); // ID 2
    group.createCustomer("Bob", "Adams", 5555, 6666, 750.25, logger);    // ID 3
    group.createCustomer("Carl", "Smith", 7777, 8888, 200.00, logger);   // ID 4


    qDebug().noquote() << "Original list:";
    qDebug().noquote() << group;

    Searcher search(group);

    qDebug().noquote() << "\nSearch by ID (3):";
    for (auto* c : search.searchByID(3)) qDebug().noquote() << *c;

    qDebug().noquote() << "\nSearch by balance (500-800):";
    for (auto* c : search.searchByBalance(500, 800)) qDebug().noquote() << *c;


    qDebug().noquote() << "\nSearch by card number (3333):";
    for (auto* c : search.searchByCardNum(3333, -1)) qDebug().noquote() << *c;

    auto all = group.getAll();

    Sorter::_sortByBalance(all, false);
    qDebug().noquote() << "\nSorted by balance descending:";
    for (auto* c : all) qDebug().noquote() << *c;

    Sorter::_sortFirstNameByAlphabet(all, true);
    qDebug().noquote() << "\nSorted by first name ascending:\n" << all;


    Sorter::_sortByID(all, true);
    qDebug().noquote() << "\nSorted by ID ascending (original order):";
    for (auto* c : all) qDebug().noquote() << *c;

    // Test encryption/decryption
    group.saveEncrypted("customers.enc", logger);
    Customers loadedGroup(logger);
    qDebug().noquote() << "\nFile is encrypted";
    loadedGroup.loadDecrypted("customers.enc", logger);

    qDebug().noquote() << "\nLoaded from encrypted file:";
    qDebug().noquote() << loadedGroup;

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
    MainWindow w(group,logger);
    w.show();
    return a.exec();
}
