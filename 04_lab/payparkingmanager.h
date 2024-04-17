#ifndef PAYPARKINGMANAGER_H
#define PAYPARKINGMANAGER_H

#include "payparking.h"
#include "vector"
#include <QLabel>
#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>

using std::vector;
class PayParkingManager
{
public:
    PayParkingManager(QTableView *ui);
    void set_pay_parking(QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif);
    void del_pay_parking(QString name, QString place, QString tarif);
    vector<PayParking> get_list();
    void set_car(QString name, QString place, QString tarif);
    void remove_car(QString name, QString place, QString tarif);
    void clear_table();
private:
    vector<PayParking> list {};
    QTableView *ui;
    void update_view();
};

#endif // PAYPARKINGMANAGER_H
