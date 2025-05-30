#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <vector>
//#include <string>
#include <QString>
#include <QDebug>
class Logger;
class Customer;

class Customers {
private:
    std::vector<Customer*> customers;
    int nextID = 1;

public:
    Customers(Logger& logger);
    Customers(const Customers& right);
    ~Customers();

    Customers& operator=(Customers& right);

    void createCustomer(QString  firstName, QString  secondName,int cardNum, int accountNum, double balance, Logger& logger);

    void setCustomerFirstName(int id, QString  newName, Logger& logger);
    void setCustomerSecondName(int id, QString  newName, Logger& logger);
    void setCustomerBalance(int id, double newBalance, Logger& logger);
    void setCustomerCardNum(int id, int newCardNum, Logger& logger);
    void setCustomerAccountNum(int id, int newAccountNum, Logger& logger);

    Customer* getByID(int id)const;
    std::vector<Customer*>& getAll();
    const std::vector<Customer*>& getAll()const;

    void copyDataByID(int id1, int id2);
    void removeByID(int id, Logger& logger);

    void add(Customer* pCust);

    QString getCustomerInfoByID(int id) const;
    QString getAllCustomersInfo() const;
    friend QDebug operator<<(QDebug debug, const Customers& group);

    void saveEncrypted(const QString & filename, Logger& logger);
    void loadDecrypted(const QString & filename, Logger& logger);
};

QDebug operator<<(QDebug debug, const std::vector<Customer*>& vec);
#endif // CUSTOMERS_H
