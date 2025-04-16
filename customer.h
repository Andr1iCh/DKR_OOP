#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <QString>
#include <QDebug>

class Logger;
class Customers;

class Customer
{
    int id;
    std::string firstName;
    std::string secondName;
    int cardNum;
    int accountNum;
    double balance;
    Customers& owner;
    friend Customers;
protected:
    Customer(std::string firstName, std::string secondName, int cardNum, int accountNum, double balance, Customers& owner, Logger& logger);
    void remove(Logger& logger);
public:
    Customer(Customer& right);
    Customer& operator=(const Customer& other);
    ~Customer();

    void setSecondName(std::string newSName, Logger& logger);
    void setFirstName(std::string newFName, Logger& logger);
    void setBalance(double newBalance, Logger& logger);
    void setCardNum(std::string newCardNum, Logger& logger);
    void setAccountNum(std::string newAccountNum, Logger& logger);


    std::string getSecondName();
    std::string getFirstName();
    double getBalance();
    int getCardNum();
    int getAccountNum();
    int getID();

    QString toString() const;

    std::string serialize();


};

QDebug operator<<(QDebug, const Customer&);
#endif // CUSTOMER_H
