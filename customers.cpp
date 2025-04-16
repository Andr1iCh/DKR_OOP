#include "customers.h"
#include "customer.h"
#include "logger.h"

#include <aes.h>
#include <modes.h>
#include <files.h>
#include <filters.h>
#include <osrng.h>
#include <sstream>

QDebug operator<<(QDebug, const Customer&);

Customers::Customers(Logger& logger) {
    logger.log("Customers object created.");
}

Customers::Customers(const Customers& right) {
    for (Customer* c : right.customers) {
        customers.push_back(new Customer(*c));
    }
    nextID = right.nextID;
}

Customers::~Customers() {
    for (Customer* c : customers) {
        delete c;
    }
    customers.clear();
}

Customers& Customers::operator=(Customers& right) {
    if (this != &right) {
        for (Customer* c : customers)
            delete c;
        customers.clear();

        for (Customer* c : right.customers)
            customers.push_back(new Customer(*c));

        nextID = right.nextID;
    }
    return *this;
}

void Customers::createCustomer(std::string firstName, std::string secondName,
                               int cardNum, int accountNum, double balance, Logger& logger)
{
    Customer* c = new Customer(firstName, secondName, cardNum, accountNum, balance, *this, logger);
    c->id = nextID++;
    customers.push_back(c);
    logger.log("Customer created: ID = " + std::to_string(c->getID()));
}

void Customers::removeByID(int id, Logger& logger) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if ((*it)->getID() == id) {
            logger.log("Deleting customer ID = " + std::to_string(id));
            delete *it;
            customers.erase(it);
            return;
        }
    }
    logger.log("Customer ID = " + std::to_string(id) + " not found for deletion.");
}

Customer* Customers::getByID(int id)const {
    for (Customer* c : customers) {
        if (c->getID() == id)
            return c;
    }
    return nullptr;
}

std::vector<Customer*> Customers::getAll() {
    return customers;
}

void Customers::add(Customer* pCust) {
    customers.push_back(pCust);
}

void Customers::setCustomerFirstName(int id, std::string newName, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setFirstName(newName, logger);
}

void Customers::setCustomerSecondName(int id, std::string newName, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setSecondName(newName, logger);
}

void Customers::setCustomerBalance(int id, double newBalance, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setBalance(newBalance, logger);
}

void Customers::setCustomerCardNum(int id, int newCardNum, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setCardNum(std::to_string(newCardNum), logger);
}

void Customers::setCustomerAccountNum(int id, int newAccountNum, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setAccountNum(std::to_string(newAccountNum), logger);
}

void Customers::copyDataByID(int id1, int id2) {
    Customer* from = getByID(id1);
    Customer* to = getByID(id2);
    if (from && to) {
        *to = *from;
    }
}

QString Customers::getCustomerInfoByID(int id) const {
    Customer* c = getByID(id);
    return c ? c->toString() : "Customer not found.";
}

QString Customers::getAllCustomersInfo() const {
    QString result;
    for (Customer* c : customers)
        result += c->toString() + "\n";
    return result;
}

QDebug operator<<(QDebug debug, const Customers& group) {
    QDebugStateSaver saver(debug);
    debug.nospace();
    for (Customer* c : group.customers)
        debug << *c << "\n";
    return debug;
}

void Customers::saveEncrypted(const std::string& filename, Logger& logger) {
    std::string data;
    for (Customer* c : customers) {
        data += c->serialize() + "\n";
    }

    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKeyWithIV(key, sizeof(key), iv);

    CryptoPP::FileSink sink(filename.c_str());
    CryptoPP::StreamTransformationFilter encryptor(enc, new CryptoPP::Redirector(sink));
    encryptor.Put(reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size());
    encryptor.MessageEnd();

    logger.log("Customer data encrypted and saved to file: " + filename);
}

void Customers::loadDecrypted(const std::string& filename, Logger& logger) {
    std::string decrypted;
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(key, sizeof(key), iv);

    CryptoPP::FileSource fs(filename.c_str(), true,
                            new CryptoPP::StreamTransformationFilter(dec,
                                                                     new CryptoPP::StringSink(decrypted)
                                                                     )
                            );

    std::istringstream iss(decrypted);
    std::string line;
    while (std::getline(iss, line)) {
        std::istringstream ls(line);
        std::string idStr, fname, sname, cardStr, accStr, balStr;

        if (std::getline(ls, idStr, ';') &&
            std::getline(ls, fname, ';') &&
            std::getline(ls, sname, ';') &&
            std::getline(ls, cardStr, ';') &&
            std::getline(ls, accStr, ';') &&
            std::getline(ls, balStr, ';')) {

            int card = static_cast<int>(std::stoi(cardStr));
            int acc = static_cast<int>(std::stoi(accStr));
            double bal = std::stod(balStr);

            this->createCustomer(fname, sname, card, acc, bal, logger);
        }
    }

    logger.log("Decrypted data successfully loaded from file: " + filename);
}

