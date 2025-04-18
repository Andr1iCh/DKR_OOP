#include "searchpanel.h"
#include "ui_searchpanel.h"
#include "customers.h"

SearchPanel::SearchPanel(Searcher& s, QWidget *parent) :
    QWidget(parent), ui(new Ui::SearchPanel), searcher(s)
{
    ui->setupUi(this);
    connect(ui->btnApply, &QPushButton::clicked, this, [=]() {
        auto result = applyFilters();
        emit filtersApplied(result);
    });

    connect(ui->btnReset, &QPushButton::clicked, this, [=]() {
        reset();
        emit filtersReset();
    });
    ui->sbMinID->setRange(0, 999999);
    ui->sbMaxID->setRange(0, 999999);

    // Card Number
    ui->sbMinCard->setRange(0, 9999);     // 4 num
    ui->sbMaxCard->setRange(0, 9999);

    // Account Number
    ui->sbMinAccount->setRange(0, 99999); // 5 num
    ui->sbMaxAccount->setRange(0, 99999);

    // Balance
    ui->sbMinBalance->setRange(0, 1e6);
    ui->sbMaxBalance->setRange(0, 1e6);

}

SearchPanel::~SearchPanel() {
    delete ui;
}

std::vector<Customer*> SearchPanel::applyFilters() {
    std::vector<Customer*> result;
    bool first = true;

    // First name
    QString valFirst = ui->leFirstName->text().trimmed();
    if (!valFirst.isEmpty()) {
        auto v = searcher.searchByFirstName(valFirst);
        result = first ? v : intersect(result, v);
        first = false;
    }

    // Second name
    QString valSecond = ui->leSecondName->text().trimmed();
    if (!valSecond.isEmpty()) {
        auto v = searcher.searchBySecondName(valSecond);
        result = first ? v : intersect(result, v);
        first = false;
    }

    // ID
    QString valID = ui->leID->text().trimmed();
    if (!valID.isEmpty()) {
        bool ok;
        int id = valID.toInt(&ok);
        if (ok) {
            auto v = searcher.searchByID(id);
            result = first ? v : intersect(result, v);
            first = false;
        }
    } else if (ui->sbMinID->value() != ui->sbMaxID->value()) {
        auto v = searcher.searchByID(ui->sbMinID->value(), ui->sbMaxID->value());
        result = first ? v : intersect(result, v);
        first = false;
    }

    // Card
    QString valCard = ui->leCard->text().trimmed();
    if (!valCard.isEmpty()) {
        bool ok;
        int num = valCard.toInt(&ok);
        if (ok) {
            auto v = searcher.searchByCardNum(num);
            result = first ? v : intersect(result, v);
            first = false;
        }
    } else if (ui->sbMinCard->value() != ui->sbMaxCard->value()) {
        auto v = searcher.searchByCardNum(ui->sbMinCard->value(), ui->sbMaxCard->value());
        result = first ? v : intersect(result, v);
        first = false;
    }

    // Account
    QString valAcc = ui->leAccount->text().trimmed();
    if (!valAcc.isEmpty()) {
        bool ok;
        int num = valAcc.toInt(&ok);
        if (ok) {
            auto v = searcher.searchByAccountNum(num);
            result = first ? v : intersect(result, v);
            first = false;
        }
    } else if (ui->sbMinAccount->value() != ui->sbMaxAccount->value()) {
        auto v = searcher.searchByAccountNum(ui->sbMinAccount->value(), ui->sbMaxAccount->value());
        result = first ? v : intersect(result, v);
        first = false;
    }

    // Balance
    QString valBal = ui->leBalance->text().trimmed();
    if (!valBal.isEmpty()) {
        bool ok;
        double bal = valBal.toDouble(&ok);
        if (ok) {
            auto v = searcher.searchByBalance(bal);
            result = first ? v : intersect(result, v);
            first = false;
        }
    } else if (ui->sbMinBalance->value() != ui->sbMaxBalance->value()) {
        auto v = searcher.searchByBalance(ui->sbMinBalance->value(), ui->sbMaxBalance->value());
        result = first ? v : intersect(result, v);
        first = false;
    }

    if (first)
        result = searcher.getAll();

    return result;
}



std::vector<Customer*> SearchPanel::intersect(
    const std::vector<Customer*>& a,
    const std::vector<Customer*>& b)
{
    std::vector<Customer*> out;
    for (auto* c : a)
        if (std::find(b.begin(), b.end(), c) != b.end())
            out.push_back(c);
    return out;
}

void SearchPanel::reset() {
    ui->leFirstName->clear();
    ui->leSecondName->clear();
    ui->leID->clear();
    ui->leCard->clear();
    ui->leAccount->clear();
    ui->leBalance->clear();

    ui->sbMinID->setValue(ui->sbMinID->minimum());
    ui->sbMaxID->setValue(ui->sbMaxID->minimum());
    ui->sbMinCard->setValue(ui->sbMinCard->minimum());
    ui->sbMaxCard->setValue(ui->sbMaxCard->minimum());
    ui->sbMinAccount->setValue(ui->sbMinAccount->minimum());
    ui->sbMaxAccount->setValue(ui->sbMaxAccount->minimum());
    ui->sbMinBalance->setValue(ui->sbMinBalance->minimum());
    ui->sbMaxBalance->setValue(ui->sbMaxBalance->minimum());
}


