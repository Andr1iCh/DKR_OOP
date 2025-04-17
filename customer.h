#ifndef CUSTOMER_H
#define CUSTOMER_H
//#include <string>
#include <QString>
#include <QDebug>

class Logger;
class Customers;

class Customer
{
    int id;
    QString  firstName;
    QString  secondName;
    int cardNum;
    int accountNum;
    double balance;
    Customers& owner;
    friend Customers;
protected:
    Customer(QString  firstName, QString  secondName, int cardNum, int accountNum, double balance, Customers& owner, Logger& logger);
    void remove(Logger& logger);
public:
    Customer(Customer& right);
    Customer& operator=(const Customer& other);
    ~Customer();

    void setSecondName(QString  newSName, Logger& logger);
    void setFirstName(QString  newFName, Logger& logger);
    void setBalance(double newBalance, Logger& logger);
    void setCardNum(QString  newCardNum, Logger& logger);
    void setAccountNum(QString  newAccountNum, Logger& logger);


    QString  getSecondName()const;
    QString  getFirstName()const;
    double getBalance()const;
    int getCardNum()const;
    int getAccountNum()const;
    int getID()const;

    QString toString() const;

    QString  serialize();


};

QDebug operator<<(QDebug, const Customer&);
#endif // CUSTOMER_H
