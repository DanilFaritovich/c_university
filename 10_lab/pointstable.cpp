#include "pointstable.h"
#include "ui_pointstable.h"

PointsTable::PointsTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PointsTable)
{
    ui->setupUi(this);
    table = this->ui->tableView;
}

PointsTable::~PointsTable()
{
    delete ui;
}
