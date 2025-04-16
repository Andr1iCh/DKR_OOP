#include "searcher.h"
#include "Customer.h"
#include "Customers.h"

std::vector<Customer*> Searcher::searchCardNumByInterval(short min, short max) {
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

std::vector<Customer*> Searcher::searchAccountNumByInterval(short min, short max) {
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

std::vector<Customer*> Searcher::searchBalanceByInterval(double min, double max) {
    std::vector<Customer*> result;
    if (max < 0.0f) {
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

