#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <vector>
#include "searcher.h"

namespace Ui {
class SearchPanel;
}

class SearchPanel : public QWidget {
    Q_OBJECT

public:
    explicit SearchPanel(Searcher& searcher, QWidget *parent = nullptr);
    ~SearchPanel();

    std::vector<Customer*> applyFilters();
    void reset();

signals:
    void filtersApplied(const std::vector<Customer*>& result);
    void filtersReset();

private:
    Ui::SearchPanel *ui;
    Searcher& searcher;

    std::vector<Customer*> intersect(
        const std::vector<Customer*>& a,
        const std::vector<Customer*>& b);
};

#endif // SEARCHPANEL_H
