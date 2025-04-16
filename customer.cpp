#include "customer.h"
#include "customers.h"
#include "logger.h"
#include <iostream>

Customer::Customer(std::string firstName, std::string secondName, short cardNum, short accountNum, double balance, Customers& owner, Logger& logger):
    firstName(std::move(firstName)),
    secondName(std::move(secondName)),
    cardNum(cardNum),
    accountNum(accountNum),
    balance(balance),
    owner(owner)
{
    logger.log("Customer created: ID=" + std::to_string(id));
}


void Customer::remove(Logger& logger)
{
    owner.removeByID(id,logger);
}

Customer::Customer(Customer& right)
    : id(right.id), firstName(right.firstName), secondName(right.secondName),
    cardNum(right.cardNum), accountNum(right.accountNum),
    balance(right.balance), owner(right.owner)
{

}

Customer& Customer::operator=(const Customer& other) {
    if (this != &other) {
        firstName = other.firstName;
        secondName = other.secondName;
        cardNum = other.cardNum;
        accountNum = other.accountNum;
        balance = other.balance;

    }
    return *this;
}

Customer::~Customer() {

}

void Customer::showCust() {
    std::cout << "ID: " << id << ", " << secondName << " " << firstName
              << ", Card: " << cardNum << ", Account: " << accountNum
              << ", Balance: $" << balance << "\n";
}

//Setters
void Customer::setSecondName(std::string newSName, Logger& logger) {
    logger.log("Changed second name of ID " + std::to_string(id) + " from " + secondName + " to " + newSName);
    secondName = newSName;
}

void Customer::setFirstName(std::string newFName, Logger& logger) {
    logger.log("Changed first name of ID " + std::to_string(id) + " from " + firstName + " to " + newFName);
    firstName = newFName;
}

void Customer::setBalance(double newBalance, Logger& logger) {
    logger.log("Changed balance of ID " + std::to_string(id) + " from " + std::to_string(balance) + " to " + std::to_string(newBalance));
    balance = newBalance;
}

void Customer::setCardNum(std::string newCardNumStr, Logger& logger) {
    short newCardNum = std::stoi(newCardNumStr);
    logger.log("Changed card number of ID " + std::to_string(id) + " from " + std::to_string(cardNum) + " to " + newCardNumStr);
    cardNum = newCardNum;
}

void Customer::setAccountNum(std::string newAccountNumStr, Logger& logger) {
    short newAccountNum = std::stoi(newAccountNumStr);
    logger.log("Changed account number of ID " + std::to_string(id) + " from " + std::to_string(accountNum) + " to " + newAccountNumStr);
    accountNum = newAccountNum;
}

//Getters
std::string Customer::getSecondName() {
    return secondName;
}

std::string Customer::getFirstName() {
    return firstName;
}

double Customer::getBalance() {
    return balance;
}

short Customer::getCardNum() {
    return cardNum;
}

short Customer::getAccountNum() {
    return accountNum;
}
int Customer::getID() {
    return id;
}


