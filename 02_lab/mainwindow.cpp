#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "book.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pay_parkin_manager(ui)
{
    ui->setupUi(this);
    pay_parkin_manager = ui;
    pay_parkin_manager.set_pay_parking("test", "test", 10, 10, 10, "test");
    pay_parkin_manager.set_pay_parking("test2", "test2", 15, 15, 15, "test2");
}

MainWindow::~MainWindow()
{
    delete ui;
}
