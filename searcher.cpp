#include "searcher.h"
#include "Customer.h"
#include "Customers.h"
#include "Searcher.h"
#include "Customer.h"
#include "Customers.h"

Searcher::Searcher(Customers& customers) : data(customers) {}

std::vector<Customer*> Searcher::searchByID(int minID, int maxID) {
    std::vector<Customer*> result;

    if (maxID == -1) {
        Customer* c = data.getByID(minID);
        if (c != nullptr)
            result.push_back(c);
    } else {
        for (Customer* c : data.getAll()) {
            int id = c->getID();
            if (id >= minID && id <= maxID) {
                result.push_back(c);
            }
        }
    }

    return result;
}

std::vector<Customer*> Searcher::searchFirstNameStartsWith(char letter) {
    std::vector<Customer*> result;
    for (Customer* c : data.getAll()) {
        if (!c->getFirstName().empty() && c->getFirstName()[0] == letter) {
            result.push_back(c);
        }
    }
    return result;
}

std::vector<Customer*> Searcher::searchSecondNameStartsWith(char letter) {
    std::vector<Customer*> result;
    for (Customer* c : data.getAll()) {
        if (!c->getSecondName().empty() && c->getSecondName()[0] == letter) {
            result.push_back(c);
        }
    }
    return result;
}

std::vector<Customer*> Searcher::searchByCardNum(short min, short max) {
    std::vector<Customer*> result;
    if (max == -1) {
        for (Customer* c : data.getAll()) {
            if (c->getCardNum() == min)
                result.push_back(c);
        }
    } else {
        for (Customer* c : data.getAll()) {
            short val = c->getCardNum();
            if (val >= min && val <= max)
                result.push_back(c);
        }
    }
    return result;
}

std::vector<Customer*> Searcher::searchByAccountNum(short min, short max) {
    std::vector<Customer*> result;
    if (max == -1) {
        for (Customer* c : data.getAll()) {
            if (c->getAccountNum() == min)
                result.push_back(c);
        }
    } else {
        for (Customer* c : data.getAll()) {
            short val = c->getAccountNum();
            if (val >= min && val <= max)
                result.push_back(c);
        }
    }
    return result;
}

std::vector<Customer*> Searcher::searchByBalance(double min, double max) {
    std::vector<Customer*> result;
    if (max < 0.0) {
        for (Customer* c : data.getAll()) {
            if (c->getBalance() == min)
                result.push_back(c);
        }
    } else {
        for (Customer* c : data.getAll()) {
            double val = c->getBalance();
            if (val >= min && val <= max)
                result.push_back(c);
        }
    }
    return result;
}


