#ifndef SORTER_H
#define SORTER_H
#include <vector>
#include "Customer.h"
#include "Customers.h"
class Sorter {
public:
    static void _sortFirstNameByAlphabet(std::vector<Customer*>& arr, bool ascending = true);
    static void _sortSecondNameByAlphabet(std::vector<Customer*>& arr, bool ascending = true);
    static void _sortByCardNum(std::vector<Customer*>& arr, bool ascending = true);
    static void _sortByAccountNum(std::vector<Customer*>& arr, bool ascending = true);
    static void _sortByBalance(std::vector<Customer*>& arr, bool ascending = true);
    static void _sortByID(std::vector<Customer*>& arr, bool ascending = true);
};

#endif // SORTER_H
