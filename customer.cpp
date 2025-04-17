#include "customer.h"
#include "customers.h"
#include "logger.h"
//#include <iostream>

Customer::Customer(QString  firstName, QString  secondName, int cardNum, int accountNum, double balance, Customers& owner, Logger& logger):
    firstName(std::move(firstName)),
    secondName(std::move(secondName)),
    cardNum(cardNum),
    accountNum(accountNum),
    balance(balance),
    owner(owner)
{
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


//Setters
void Customer::setSecondName(QString newSName, Logger& logger) {
    logger.log(QString("Changed second name of ID %1 from %2 to %3")
                   .arg(id).arg(secondName).arg(newSName));
    secondName = newSName;
}

void Customer::setFirstName(QString newFName, Logger& logger) {
    logger.log(QString("Changed first name of ID %1 from %2 to %3")
                   .arg(id).arg(firstName).arg(newFName));
    firstName = newFName;
}

void Customer::setBalance(double newBalance, Logger& logger) {
    logger.log(QString("Changed balance of ID %1 from %2 to %3")
                   .arg(id).arg(balance).arg(newBalance));
    balance = newBalance;
}

void Customer::setCardNum(QString newCardNumStr, Logger& logger) {
    int newCardNum = newCardNumStr.toInt();
    logger.log(QString("Changed card number of ID %1 from %2 to %3")
                   .arg(id).arg(cardNum).arg(newCardNumStr));
    cardNum = newCardNum;
}

void Customer::setAccountNum(QString newAccountNumStr, Logger& logger) {
    int newAccountNum = newAccountNumStr.toInt();
    logger.log(QString("Changed account number of ID %1 from %2 to %3")
                   .arg(id).arg(accountNum).arg(newAccountNumStr));
    accountNum = newAccountNum;
}


//Getters
QString  Customer::getSecondName()const {
    return secondName;
}

QString  Customer::getFirstName()const {
    return firstName;
}

double Customer::getBalance()const {
    return balance;
}

int Customer::getCardNum() const{
    return cardNum;
}

int Customer::getAccountNum() const{
    return accountNum;
}
int Customer::getID() const{
    return id;
}

QString Customer::toString() const {
    return QString("ID: %1 | %2 %3 | Card: %4 | Account: %5 | Balance: %6")
    .arg(id).arg(secondName).arg(firstName).arg(cardNum).arg(accountNum).arg(balance);
}


QDebug operator<<(QDebug debug, const Customer& c) {
    QDebugStateSaver saver(debug);
    debug.nospace() << c.toString();
    return debug;
}

QString Customer::serialize() {
    return QString("%1;%2;%3;%4;%5;%6")
    .arg(id)
        .arg(firstName, secondName)
        .arg(cardNum)
        .arg(accountNum)
        .arg(balance);
}



