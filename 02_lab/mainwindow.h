#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <payparkingmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PayParkingManager pay_parkin_manager;
};

#endif // MAINWINDOW_H
