#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <vector>
#include <string>
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

    void createCustomer(std::string firstName, std::string secondName,short cardNum, short accountNum, double balance, Logger& logger);

    void setCustomerFirstName(int id, std::string newName, Logger& logger);
    void setCustomerSecondName(int id, std::string newName, Logger& logger);
    void setCustomerBalance(int id, double newBalance, Logger& logger);
    void setCustomerCardNum(int id, short newCardNum, Logger& logger);
    void setCustomerAccountNum(int id, short newAccountNum, Logger& logger);

    Customer* getByID(int id);
    std::vector<Customer*> getAll();

    void copyDataByID(int id1, int id2);
    void removeByID(int id, Logger& logger);

    void add(Customer* pCust);
    int generateID();
};

#endif // CUSTOMERS_H
