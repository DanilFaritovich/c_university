#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"

MainWindow::MainWindow(QWidget *parent, PayParkingManager pay_parking_manager)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pay_parking_manager(pay_parking_manager)
{
    ui->setupUi(this);
    this->pay_parking_manager = ui->MainTableView;
    this->pay_parking_manager.set_pay_parking("1", "1", 10, 10, 10, "1");
    this->pay_parking_manager.set_pay_parking("2", "2", 15, 15, 15, "2");
    this->pay_parking_manager.set_pay_parking("3", "3", 15, 0, 0, "3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clear_clicked()
{
    this->pay_parking_manager.clear_table();
}


void MainWindow::on_btn_add_column_clicked()
{
    Form *f = new Form();
    f->set_pay_parking_manager(&this->pay_parking_manager);
    f->setAttribute(Qt::WA_DeleteOnClose);
    f->show();
    for (auto addr : this->pay_parking_manager.get_list()){
        qInfo() << addr.get_name();
    }
    //this->pay_parking_manager.set_pay_parking();
}


void MainWindow::on_btn_del_column_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {

        this->pay_parking_manager.del_pay_parking
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}


void MainWindow::on_btn_set_car_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {
        this->pay_parking_manager.set_car
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}


void MainWindow::on_btn_remove_car_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {
        this->pay_parking_manager.remove_car
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}
