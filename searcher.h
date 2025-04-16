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

    std::vector<Customer*> searchByID(int minID, int maxID = -1);
    std::vector<Customer*> searchFirstNameStartsWith(char letter);
    std::vector<Customer*> searchSecondNameStartsWith(char letter);
    std::vector<Customer*> searchByCardNum(int min, int max = -1);
    std::vector<Customer*> searchByAccountNum(int min, int max = -1);
    std::vector<Customer*> searchByBalance(double min, double max = -1.0);
};
#endif // SEARCHER_H
