#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"

#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>

AddCustomerDialog::AddCustomerDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
     setWindowTitle("Add customer");
    auto* nameVal = new QRegularExpressionValidator(
        QRegularExpression("^[A-Za-zА-Яа-яЁёЇїІіЄєҐґ]+$"), this);
    ui->lineFirstName ->setValidator(nameVal);
    ui->lineSecondName->setValidator(nameVal);

    ui->lineCard   ->setValidator(new QIntValidator(1, 9999,  this));
    ui->lineAccount->setValidator(new QIntValidator(1, 99999, this));
    ui->lineBalance->setValidator(new QDoubleValidator(-1e9, 1e9, 2, this));

}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}

QString AddCustomerDialog::firstName()  const
{
    return ui->lineFirstName ->text().trimmed();
}

QString AddCustomerDialog::secondName() const
{
    return ui->lineSecondName->text().trimmed();
}

int     AddCustomerDialog::card()       const
{
    return ui->lineCard   ->text().toInt();
}

int     AddCustomerDialog::account()    const
{
    return ui->lineAccount->text().toInt();
}

double  AddCustomerDialog::balance()    const
{
    return ui->lineBalance->text().toDouble();
}
