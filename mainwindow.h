#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "searchpanel.h"
#include "searcher.h"

class Customers;
class Logger;
class Customer;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Customers& customers, Logger& logger, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayFiltered(const std::vector<Customer*>& list);

private slots:
    void onTableCellChanged(int row, int columnIndex);
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void onColumnHeaderClicked(int column);
    void on_btnEncrypt_clicked();
    void on_btnLoad_clicked();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow *ui;

    Customers& customers;
    Logger& logger;

    std::vector<Customer*> currentTableView;

    Searcher searcher;
    SearchPanel* searchPanel = nullptr;
    QDockWidget* searchDock = nullptr;

    int lastSortedColumn = -1;
    Qt::SortOrder lastOrder = Qt::AscendingOrder;

    void tableInit();
    void fillTable();
    void fillTable(const std::vector<Customer*>&);
    void updateTableFontSize();
};

#endif // MAINWINDOW_H
