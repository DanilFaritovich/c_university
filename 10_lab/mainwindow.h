#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    ~MainWindow();

private slots:
    void on_save_triggered();

    void on_load_triggered();

private:
    Ui::MainWindow *ui;
    Widget *widget;
};
#endif // MAINWINDOW_H
