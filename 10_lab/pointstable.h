#ifndef POINTSTABLE_H
#define POINTSTABLE_H

#include <QWidget>
#include <QTableView>

namespace Ui {
class PointsTable;
}

class PointsTable : public QWidget
{
    Q_OBJECT

public:
    explicit PointsTable(QWidget *parent = nullptr);
    QTableView* table;
    ~PointsTable();

private:
    Ui::PointsTable *ui;
};

#endif // POINTSTABLE_H
