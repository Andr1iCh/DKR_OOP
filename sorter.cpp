#include "sorter.h"

#include "Sorter.h"
#include "Customer.h"
#include <algorithm>

void Sorter::_sortFirstNameByAlphabet(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getFirstName() < b->getFirstName()
                         : a->getFirstName() > b->getFirstName();
    });
}

void Sorter::_sortSecondNameByAlphabet(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getSecondName() < b->getSecondName()
                         : a->getSecondName() > b->getSecondName();
    });
}

void Sorter::_sortByCardNum(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getCardNum() < b->getCardNum()
                         : a->getCardNum() > b->getCardNum();
    });
}

void Sorter::_sortByAccountNum(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getAccountNum() < b->getAccountNum()
                         : a->getAccountNum() > b->getAccountNum();
    });
}

void Sorter::_sortByBalance(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getBalance() < b->getBalance()
                         : a->getBalance() > b->getBalance();
    });
}

void Sorter::_sortByID(std::vector<Customer*>& arr, bool ascending) {
    std::sort(arr.begin(), arr.end(), [ascending](Customer* a, Customer* b) {
        return ascending ? a->getID() < b->getID()
                         : a->getID() > b->getID();
    });
}

