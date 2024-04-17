#ifndef PAYPARKINGMANAGER_H
#define PAYPARKINGMANAGER_H

#include "payparking.h"
#include "vector"
#include <QTableView>
#include <QLabel>
#include <QStandardItemModel>

using std::vector;
class PayParkingManager
{
public:
    PayParkingManager();
    void set_pay_parking(QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif);
private:
    vector<PayParking> list {};
    QTableView *ui;
    void update_view();
};

#endif // PAYPARKINGMANAGER_H
