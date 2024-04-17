#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, PayParkingManager pay_parking_manager)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pay_parking_manager(pay_parking_manager)
{
    ui->setupUi(this);
    this->pay_parking_manager = ui->MainTableView;
    //this->pay_parking_manager.set_pay_parking("1", "1", 10, 10, 10, "1");
    //this->pay_parking_manager.set_pay_parking("2", "2", 15, 15, 15, "2");
    //this->pay_parking_manager.set_pay_parking("3", "3", 15, 0, 0, "3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clear_clicked()
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
        this->pay_parking_manager.clear_table();
    }
    else
        return;
}


void MainWindow::on_btn_add_column_clicked()
{
    Form *f = new Form();
    f->set_pay_parking_manager(&this->pay_parking_manager);
    f->setAttribute(Qt::WA_DeleteOnClose);
    f->show();
    for (auto addr : this->pay_parking_manager.get_list()){
        qInfo() << addr.get_name();
    }
    //this->pay_parking_manager.set_pay_parking();
}


void MainWindow::on_btn_del_column_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {

        this->pay_parking_manager.del_pay_parking
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}


void MainWindow::on_btn_set_car_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {
        this->pay_parking_manager.set_car
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}


void MainWindow::on_btn_remove_car_clicked()
{
    QModelIndexList selected = ui->MainTableView->selectionModel()->selectedRows();
    for (auto row : selected)
    {

        this->pay_parking_manager.remove_car
        (
            row.sibling(row.row(), 0).data().toString(),
            row.sibling(row.row(), 1).data().toString(),
            row.sibling(row.row(), 5).data().toString()
        );
    }
}

QDataStream& operator<<(QDataStream& stream, PayParkingManager& pay_parking_manager)
{
    for (auto pay_parking : pay_parking_manager.get_list())
    {
        stream << pay_parking.get_name()
               << pay_parking.get_place()
               << pay_parking.get_free_space_count()
               << pay_parking.get_occupied_space_count()
               << pay_parking.get_remove_cars_count()
               << pay_parking.get_tarif();
    }
    return stream;
}

QDataStream& operator>>(QDataStream& stream, PayParkingManager& pay_parking_manager)
{
    QString name, place, tarif;
    int space_count, occupied_space_count, remove_cars_count;
    while (true)
    {
        stream >> name
            >> place
            >> space_count
            >> occupied_space_count
            >> remove_cars_count
            >> tarif;
        if (name == "")
        {
            break;
        }
        else
        {
            pay_parking_manager.set_pay_parking(name,
                                                place,
                                                space_count,
                                                occupied_space_count,
                                                remove_cars_count,
                                                tarif);
        }
    }
    return stream;
}

void MainWindow::on_action_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(
        this,
        tr("Save File"),
        "untitled.dat",
        tr("(*.dat)")
    );
    qInfo() << file_name;
    if (!file_name.isNull())
    {
        // Создаём объект файла
        QFile file(file_name);
        // Пытаемся открыть файл в необходимом режиме
        if (file.open(QIODevice::WriteOnly))
        {
            QDataStream dataStream(&file);
            dataStream << pay_parking_manager;
            file.close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Ошибка в чтении файла!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}


void MainWindow::on_action_2_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(
        this,
        tr("Save File"),
        "untitled.dat",
        tr("(*.dat)")
        );
    qInfo() << file_name;
    if (!file_name.isNull())
    {
        // Создаём объект файла
        QFile file(file_name);
        // Пытаемся открыть файл в необходимом режиме
        if (file.open(QIODevice::ReadOnly))
        {
            QDataStream dataStream(&file);
            this->pay_parking_manager.clear_table();
            dataStream >> this->pay_parking_manager;
            file.close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Ошибка в чтении файла!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

