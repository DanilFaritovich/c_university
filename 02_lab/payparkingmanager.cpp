#include "payparkingmanager.h"
#include <iostream>
#include <string>


PayParkingManager::PayParkingManager(Ui::MainWindow *ui)
{
    this->ui = ui->MainTableView;
};

void PayParkingManager::set_pay_parking(QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif)
{
    this->list.push_back(PayParking(name, place, free_space_count, occupied_space_count, remove_cars_count, tarif));
    this->update_view();
};

void PayParkingManager::update_view()
{
    QStandardItemModel* model = new QStandardItemModel(this->list.size(), 6);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Place");
    model->setHeaderData(2, Qt::Horizontal, "Free");
    model->setHeaderData(3, Qt::Horizontal, "occupied");
    model->setHeaderData(4, Qt::Horizontal, "remove");
    model->setHeaderData(5, Qt::Horizontal, "tarif");
    int row = 0;
    for (PayParking& pay_parking : this->list){
        model->setItem(row, 0, new QStandardItem(pay_parking.get_name()));
        model->setItem(row, 1, new QStandardItem(pay_parking.get_place()));
        model->setItem(row, 2, new QStandardItem(QString::number(pay_parking.get_free_space_count())));
        model->setItem(row, 3, new QStandardItem(QString::number(pay_parking.get_occupied_space_count())));
        model->setItem(row, 4, new QStandardItem(QString::number(pay_parking.get_remove_cars_count())));
        model->setItem(row, 5, new QStandardItem(pay_parking.get_tarif()));
        row++;
    }
    this->ui->setModel(model);
};
