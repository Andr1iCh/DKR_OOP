#ifndef SEARCHER_H
#define SEARCHER_H
#include <vector>
#include "Customer.h"
#include "Customers.h"

class Searcher {
private:
    Customers& data;

public:
    Searcher(Customers& customers);

    Customer* searchByID(int id);
    std::vector<Customer*> searchFirstNameStartsWith(char letter);
    std::vector<Customer*> searchSecondNameStartsWith(char letter);
    std::vector<Customer*> searchByCardNum(short number);
    std::vector<Customer*> searchByAccountNum(short number);
    std::vector<Customer*> searchCardNumByInterval(short min, short max);
    std::vector<Customer*> searchAccountNumByInterval(short min, short max);
    std::vector<Customer*> searchBalanceByInterval(double min, double max);
};
#endif // SEARCHER_H
