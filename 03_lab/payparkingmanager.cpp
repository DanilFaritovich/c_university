#include "payparkingmanager.h"
#include <QMessageBox>


PayParkingManager::PayParkingManager(QTableView *ui)
{
    this->ui = ui;
};

void PayParkingManager::set_pay_parking(QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif)
{
    this->list.push_back(PayParking(name, place, free_space_count, occupied_space_count, remove_cars_count, tarif));
    for (auto addr : list){
        qInfo() << addr.get_name();
    }
    qInfo() << "\n";
    this->update_view();
};

vector<PayParking> PayParkingManager::get_list(){
    return this->list;
}

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
        qInfo() << pay_parking.get_name();
        model->setItem(row, 0, new QStandardItem(pay_parking.get_name()));
        model->setItem(row, 1, new QStandardItem(pay_parking.get_place()));
        model->setItem(row, 2, new QStandardItem(QString::number(pay_parking.get_free_spaces())));
        model->setItem(row, 3, new QStandardItem(QString::number(pay_parking.get_occupied_space_count())));
        model->setItem(row, 4, new QStandardItem(QString::number(pay_parking.get_remove_cars_count())));
        model->setItem(row, 5, new QStandardItem(pay_parking.get_tarif()));
        row++;
    }
    qInfo() << "\n";
    this->ui->setModel(model);
};

void PayParkingManager::del_pay_parking(QString name, QString place, QString tarif)
{
    vector<PayParking> list {};
    for (auto parking : this->list)
    {
        if (name == parking.get_name() and place == parking.get_place() and tarif == parking.get_tarif())
        {
            continue;
        }
        list.push_back(parking);
    }
    this->list = list;
    this->update_view();
}

void PayParkingManager::set_car(QString name, QString place, QString tarif){
    for (auto& parking : this->list)
    {
        if (name == parking.get_name() and place == parking.get_place() and tarif == parking.get_tarif())
        {
            parking.set_car();
            this->update_view();
            return;
        }
    }
}

void PayParkingManager::remove_car(QString name, QString place, QString tarif){
    for (auto& parking : this->list)
    {
        if (name == parking.get_name() and place == parking.get_place() and tarif == parking.get_tarif())
        {
            parking.remove_car();
            this->update_view();
            return;
        }
    }
}

void PayParkingManager::clear_table()
{
    QMessageBox msgBox;
    msgBox.setText("Внимательно прочтите!");
    msgBox.setInformativeText("Ок - Точно удаляю\nCancel - Передумал");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int res = msgBox.exec();
    if (res == QMessageBox::Ok)
    {
        this->list.clear();
        this->update_view();
    }
    else
        return;
}
