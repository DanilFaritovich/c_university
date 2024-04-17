#include "widget.h"
#include "payparking.h"
#include "ui_widget.h"
#include <QMessageBox>

PayParking pay_parking(
    "Парковка",
    "Челны",
    30,
    "Платный"
    );

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Parking)
{
    ui->setupUi(this);
    this->ui->name->setText(QString::fromStdString(pay_parking.get_name()));
    this->ui->place->setText(QString::fromStdString(pay_parking.get_place()));
    this->ui->space_count->setText(QString::fromStdString(std::to_string(pay_parking.get_free_space_count())));
    this->ui->tarif->setText(QString::fromStdString(pay_parking.get_tarif()));
    this->ui->occuped_count->setText(QString::fromStdString(std::to_string(pay_parking.get_occuped_count())));
    this->ui->free_spaces_count->setText(QString::fromStdString(std::to_string(pay_parking.get_free_spaces())));
    this->ui->exit_count->setText(QString::fromStdString(std::to_string(pay_parking.get_remove_cars_count())));
}

Widget::~Widget()
{
    delete ui;
}

//Widget::Widget(QLabel *parent)

void Widget::on_btn_set_clicked()
{
    if (pay_parking.get_free_spaces() > 0){
        pay_parking.set_car();
        this->ui->occuped_count->setText(QString::fromStdString(std::to_string(pay_parking.get_occuped_count())));
        this->ui->free_spaces_count->setText(QString::fromStdString(std::to_string(pay_parking.get_free_spaces())));
    }
    else{
        QMessageBox::critical(this, "Предупреждение", "Нет свободных мест", QMessageBox::Ok);
    }
}


void Widget::on_btn_remove_clicked()
{
    if (pay_parking.get_occuped_count() > 0){
        pay_parking.remove_car();
        this->ui->occuped_count->setText(QString::fromStdString(std::to_string(pay_parking.get_occuped_count())));
        this->ui->free_spaces_count->setText(QString::fromStdString(std::to_string(pay_parking.get_free_spaces())));
        this->ui->exit_count->setText(QString::fromStdString(std::to_string(pay_parking.get_remove_cars_count())));
    }
    else{
        QMessageBox::critical(this, "Предупреждение", "Машин на парковке нет", QMessageBox::Ok);
    }
}

