#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

class Logger;
class Customers;

class Customer
{
    int id;
    std::string firstName;
    std::string secondName;
    short cardNum;
    short accountNum;
    double balance;
    Customers& owner;
    friend Customers;
protected:
    Customer(std::string firstName, std::string secondName, short cardNum, short accountNum, double balance, Customers& owner, Logger& logger);
    void remove(Logger& logger);
public:
    Customer(Customer& right);
    Customer& operator=(const Customer& other);
    ~Customer();

    void showCust();
    void setSecondName(std::string newSName, Logger& logger);
    void setFirstName(std::string newFName, Logger& logger);
    void setBalance(double newBalance, Logger& logger);
    void setCardNum(std::string newCardNum, Logger& logger);
    void setAccountNum(std::string newAccountNum, Logger& logger);


    std::string getSecondName();
    std::string getFirstName();
    double getBalance();
    short getCardNum();
    short getAccountNum();
    int getID();

};

#endif // CUSTOMER_H
