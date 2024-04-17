#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "payparkingmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, PayParkingManager pay_parking_manager = nullptr);
    ~MainWindow();

private slots:
    void on_btn_clear_clicked();

    void on_btn_add_column_clicked();

    void on_btn_del_column_clicked();

    void on_btn_set_car_clicked();

    void on_btn_remove_car_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PayParkingManager pay_parking_manager;
};
#endif // MAINWINDOW_H
