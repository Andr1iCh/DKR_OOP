    #ifndef MAINWINDOW_H
    #define MAINWINDOW_H


    #include <QMainWindow>
    #include "searchpanel.h"
    #include "searcher.h"
    #include <QDockWidget>
    class Customers;
    class Logger;

    QT_BEGIN_NAMESPACE
    namespace Ui {
    class MainWindow;
    }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(Customers& customers,Logger& log, QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        //void on_btnShow_clicked();
        void onTableCellChanged(int row, int columnIndex);
        void on_btnAdd_clicked();
        void onColumnHeaderClicked(int column);
        void on_btnDelete_clicked();

    public slots:
        void displayFiltered(const std::vector<Customer*>& list);

    private:
        Ui::MainWindow *ui;

        Customers& customers;
        Logger& logger;

        void resizeEvent(QResizeEvent* event) override;
        void updateTableFontSize();

        void tableInit();
        void fillTable();

        int lastSortedColumn = -1;
        Qt::SortOrder lastOrder = Qt::AscendingOrder;

        Searcher searcher;
        SearchPanel* searchPanel = nullptr;
        QDockWidget* searchDock = nullptr;
        void fillTable(const std::vector<Customer*>& list);
        std::vector<Customer*> currentTableView;
    };
    #endif // MAINWINDOW_H
