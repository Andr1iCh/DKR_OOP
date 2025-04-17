#include "customers.h"
#include "customer.h"
#include "logger.h"

#include "aes.h"
#include "modes.h"
#include "files.h"
#include "filters.h"

#include <filesystem>
#include <QFileInfo>

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

void Customers::createCustomer(QString firstName, QString secondName,
                               int cardNum, int accountNum, double balance, Logger& logger)
{
    Customer* c = new Customer(firstName, secondName, cardNum, accountNum, balance, *this, logger);
    c->id = nextID++;
    customers.push_back(c);
    logger.log(QString("Customer created: ID = %1").arg(c->getID()));
}

void Customers::removeByID(int id, Logger& logger) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if ((*it)->getID() == id) {
            logger.log(QString("Deleting customer ID = %1").arg(id));
            delete *it;
            customers.erase(it);
            return;
        }
    }
    logger.log(QString("Customer ID = %1 not found for deletion.").arg(id));
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

void Customers::setCustomerFirstName(int id, QString newName, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setFirstName(newName, logger);
}

void Customers::setCustomerSecondName(int id, QString newName, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setSecondName(newName, logger);
}

void Customers::setCustomerBalance(int id, double newBalance, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setBalance(newBalance, logger);
}

void Customers::setCustomerCardNum(int id, int newCardNum, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setCardNum(QString::number(newCardNum), logger);
}

void Customers::setCustomerAccountNum(int id, int newAccountNum, Logger& logger) {
    Customer* c = getByID(id);
    if (c) c->setAccountNum(QString::number(newAccountNum), logger);
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
QDebug operator<<(QDebug debug, const std::vector<Customer*>& vec) {
    QDebugStateSaver saver(debug);
    debug.nospace();
    for (const Customer* c : vec) {
        debug << *c << "\n";
    }
    return debug;
}

void Customers::saveEncrypted(const QString& filename, Logger& logger) {
    std::filesystem::create_directory("temp");

    QString data;
    for (Customer* c : customers) {
        data += c->serialize() + "\n";  // serialize повертає QString
    }

    std::string dataStd = data.toStdString();

    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKeyWithIV(key, sizeof(key), iv);

    std::string fullPath = "temp/" + filename.toStdString();
    CryptoPP::FileSink sink(fullPath.c_str());
    CryptoPP::StreamTransformationFilter encryptor(enc, new CryptoPP::Redirector(sink));
    encryptor.Put(reinterpret_cast<const CryptoPP::byte*>(dataStd.data()), dataStd.size());
    encryptor.MessageEnd();

    QFileInfo fileinfo(filename);
    logger.log(QString("Customer data encrypted and saved to file: %1\nPATH: %2").arg(filename,fileinfo.absoluteFilePath()));
}

void Customers::loadDecrypted(const QString& filename, Logger& logger) {
    std::string decrypted;
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0};
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE] = {0};

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(key, sizeof(key), iv);

    std::string fullPath = "temp/" + filename.toStdString();
    CryptoPP::FileSource fs(fullPath.c_str(), true,
                            new CryptoPP::StreamTransformationFilter(dec, new CryptoPP::StringSink(decrypted)));

    QString decryptedStr = QString::fromStdString(decrypted);
    QStringList lines = decryptedStr.split('\n', Qt::SkipEmptyParts);

    for (const QString& line : lines) {
        QStringList fields = line.split(';');
        if (fields.size() == 6) {
            QString fname = fields[1];
            QString sname = fields[2];
            int card = fields[3].toInt();
            int acc = fields[4].toInt();
            double bal = fields[5].toDouble();

            this->createCustomer(fname, sname, card, acc, bal, logger);
        }
    }
    logger.log(QString("Decrypted data successfully loaded from file: %1").arg(filename));
}


