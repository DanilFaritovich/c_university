#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "payparkingmanager.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void set_pay_parking_manager(PayParkingManager *pay_parking_manager);
    PayParkingManager get_pay_parking_manager();

private slots:
    void on_btn_add_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::Form *ui;
    PayParkingManager *pay_parking_manager;
};

#endif // FORM_H
