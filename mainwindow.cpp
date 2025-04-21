#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "customers.h"
#include "customer.h"
#include "logger.h"
#include "sorter.h"
#include <QTableWidgetItem>
#include <QResizeEvent>
#include <QInputDialog>

#include "addcustomerdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(Customers& cust, Logger& log, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    customers(cust), logger(log), searcher(customers)
{
    ui->setupUi(this);
    tableInit();
    fillTable();
    setWindowTitle("CustomerManager");
    setWindowIcon(QIcon("resources/icons/icon.ico"));
    searchPanel = new SearchPanel(searcher, this);
    ui->searchContainer->setLayout(new QVBoxLayout);
    ui->searchContainer->layout()->addWidget(searchPanel);


    connect(ui->tableWidget, &QTableWidget::cellChanged,
            this,           &MainWindow::onTableCellChanged);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &MainWindow::onColumnHeaderClicked);
    connect(searchPanel, &SearchPanel::filtersApplied, this, &MainWindow::displayFiltered);
    connect(searchPanel, &SearchPanel::filtersReset, this, [=]() {
        fillTable();
    });



}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tableInit()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionsClickable(true);
    ui->tableWidget->horizontalHeader()->setSortIndicatorShown(true);

    QFont baseFont;
    baseFont.setPointSize(10);
    ui->tableWidget->setFont(baseFont);

    ui->tableWidget->setHorizontalHeaderLabels(
        {"ID", "First Name", "Second Name",
         "Card", "Account", "Balance"});
    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 130);
    ui->tableWidget->setColumnWidth(2, 130);
    ui->tableWidget->setColumnWidth(3, 110);
    ui->tableWidget->setColumnWidth(4, 110);
    ui->tableWidget->setColumnWidth(5, 150);


}

void MainWindow::fillTable() {
    fillTable(customers.getAll());
}



void MainWindow::fillTable(const std::vector<Customer*>& list) {
    currentTableView = list;
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(static_cast<int>(list.size()));

    for (int row = 0; row < list.size(); ++row) {
        const Customer* c = list[row];

        auto* idItem  = new QTableWidgetItem(QString::number(c->getID()));
        auto* fItem   = new QTableWidgetItem(c->getFirstName());
        auto* sItem   = new QTableWidgetItem(c->getSecondName());
        auto* cardIt  = new QTableWidgetItem(QString::number(c->getCardNum()));
        auto* accIt   = new QTableWidgetItem(QString::number(c->getAccountNum()));
        auto* balIt   = new QTableWidgetItem(QString::number(c->getBalance(),'f',2));

        for (auto* it : { idItem,fItem,sItem,cardIt,accIt,balIt })
            it->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(row, 0, idItem);
        ui->tableWidget->setItem(row, 1, fItem);
        ui->tableWidget->setItem(row, 2, sItem);
        ui->tableWidget->setItem(row, 3, cardIt);
        ui->tableWidget->setItem(row, 4, accIt);
        ui->tableWidget->setItem(row, 5, balIt);
    }

    ui->tableWidget->blockSignals(false);
}




/*void MainWindow::on_btnShow_clicked()
{
    ui->tableWidget->setCurrentCell(-1, -1);
    fillTable();
}*/

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    qDebug() << "resizeEvent called!";
    updateTableFontSize();
}

void MainWindow::updateTableFontSize()
{
    int width = ui->tableWidget->width();
    int scaledFontSize = std::clamp(width / 70, 10, 25);

    QFont font = ui->tableWidget->font();
    font.setPointSize(scaledFontSize);
    ui->tableWidget->setFont(font);
}


void MainWindow::onTableCellChanged(int row, int column)
{
    const auto& list = customers.getAll();
    if (row < 0 || row >= static_cast<int>(list.size())) {
        return;
    }

    Customer* c = list[row];
    QTableWidgetItem* item = ui->tableWidget->item(row, column);
    if (!item) {
        return;
    }

    QString v = item->text().trimmed();
    bool flagConvertion = false;

    bool isAllDigits = !v.isEmpty();
    for (QChar ch : v) {
        if (!ch.isDigit()) {
            isAllDigits = false;
            break;
        }
    }

    bool isName = !v.isEmpty() && v.indexOf(QRegularExpression("\\d")) == -1;

    switch (column) {
    case 1:
        if (isName) {
            customers.setCustomerFirstName(c->getID(), v, logger);
        }
        break;
    case 2:
        if (isName) {
            customers.setCustomerSecondName(c->getID(), v, logger);
        }
        break;
    case 3:
        if (isAllDigits && v.size() == 4) {
            int card = v.toInt(&flagConvertion);
            if (flagConvertion) {
                customers.setCustomerCardNum(c->getID(), card, logger);
            }
        }
        break;
    case 4:
        if (isAllDigits && v.size() == 5) {
            int acc = v.toInt(&flagConvertion);
            if (flagConvertion) {
                customers.setCustomerAccountNum(c->getID(), acc, logger);
            }
        }
        break;
    case 5: {
        double bal = v.toDouble(&flagConvertion);
        if (flagConvertion) {
            customers.setCustomerBalance(c->getID(), bal, logger);
        }
        break;
    }
    default:
        break;
    }

    fillTable();
}



void MainWindow::on_btnAdd_clicked()
{
    AddCustomerDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted)
        return;

    if (dlg.firstName().isEmpty() || dlg.secondName().isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "Name fields cannot be empty.");
        return;
    }
    if (QString::number(dlg.card()).length() != 4 ||
        QString::number(dlg.account()).length() != 5) {
        QMessageBox::warning(this, "Invalid input","Card must be 4 digits and Account 5 digits.");
        return;
    }

    customers.createCustomer(dlg.firstName(), dlg.secondName(),dlg.card(),dlg.account(),dlg.balance(),logger);
    fillTable();
}

void MainWindow::onColumnHeaderClicked(int columnIndex)
{
    if (columnIndex == lastSortedColumn) {
        if (lastOrder == Qt::AscendingOrder) {
            lastOrder = Qt::DescendingOrder;
        } else {
            lastOrder = Qt::AscendingOrder;
        }
    } else {
        lastSortedColumn = columnIndex;
        lastOrder = Qt::AscendingOrder;
    }

    auto& vec = currentTableView;

    switch (columnIndex) {
    case 0: Sorter::_sortByID(vec,            lastOrder == Qt::AscendingOrder);
        break;
    case 1: Sorter::_sortFirstNameByAlphabet(vec,lastOrder == Qt::AscendingOrder);
        break;
    case 2: Sorter::_sortSecondNameByAlphabet(vec,lastOrder == Qt::AscendingOrder);
        break;
    case 3: Sorter::_sortByCardNum(vec,       lastOrder == Qt::AscendingOrder);
        break;
    case 4: Sorter::_sortByAccountNum(vec,    lastOrder == Qt::AscendingOrder);
        break;
    case 5: Sorter::_sortByBalance(vec,       lastOrder == Qt::AscendingOrder);
        break;
    default: break;
    }

    ui->tableWidget->horizontalHeader()
        ->setSortIndicator(columnIndex, lastOrder);

    fillTable(currentTableView);
}

void MainWindow::displayFiltered(const std::vector<Customer*>& list) {
    fillTable(list);
}

bool shouldDelete(Customer* c, const std::vector<int>& idsToDelete) {
    for (int id : idsToDelete) {
        if (c->getID() == id)
            return true;
    }
    return false;
}

void MainWindow::on_btnDelete_clicked()
{
    QList<QModelIndex> selectedRows = ui->tableWidget->selectionModel()->selectedRows();

    if (selectedRows.isEmpty())
        return;

    std::vector<int> idsToDelete;
    for (const QModelIndex& index : selectedRows) {
        int row = index.row();
        if (row >= 0 && row < static_cast<int>(currentTableView.size())) {
            idsToDelete.push_back(currentTableView[row]->getID());
        }
    }

    // Delete from currentTableView
    std::vector<Customer*> updatedView;
    for (Customer* c : currentTableView) {
        if (!shouldDelete(c, idsToDelete)) {
            updatedView.push_back(c);
        }
    }

    // Delete from Customers
    for (int id : idsToDelete) {
        customers.removeByID(id, logger);
    }

    currentTableView = updatedView;
    fillTable(currentTableView);
}

void MainWindow::on_btnEncrypt_clicked()
{
    customers.saveEncrypted("customers.enc",logger);
    QMessageBox::information(this, "Success", "Encrypted file saved as customers.enc");

}

void MainWindow::on_btnLoad_clicked()
{
    customers.loadDecrypted("customers.enc", logger);
    fillTable();
    ui->statusbar->showMessage("Decrypted data loaded from customers.enc", 3000);
}
