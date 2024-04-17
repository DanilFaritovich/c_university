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
    friend QDataStream& operator<<(QDataStream& stream, PayParkingManager& pay_parking_manager);
    friend QDataStream& operator>>(QDataStream& stream, PayParkingManager& pay_parking_manager);
    ~MainWindow();

private slots:
    void on_btn_clear_clicked();

    void on_btn_add_column_clicked();

    void on_btn_del_column_clicked();

    void on_btn_set_car_clicked();

    void on_btn_remove_car_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    PayParkingManager pay_parking_manager;
};
#endif // MAINWINDOW_H
