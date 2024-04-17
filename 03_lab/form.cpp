#include "form.h"
#include "ui_form.h"
#include "payparkingmanager.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
    , pay_parking_manager(nullptr)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::set_pay_parking_manager(PayParkingManager *pay_parking_manager)
{
    this->pay_parking_manager = pay_parking_manager;
}

void Form::on_btn_add_clicked()
{
    qInfo() << this->ui->text_name->toPlainText();
    qInfo() << this->ui->text_place->toPlainText();
    qInfo() << this->ui->text_free_space->toPlainText().toInt();
    qInfo() << this->ui->text_occuped_space->toPlainText().toInt();
    qInfo() << this->ui->text_exit_cars->toPlainText().toInt();
    qInfo() << this->ui->text_tarif->toPlainText() << "\n";
    this->pay_parking_manager->set_pay_parking(
        this->ui->text_name->toPlainText(),
        this->ui->text_place->toPlainText(),
        this->ui->text_free_space->toPlainText().toInt(),
        this->ui->text_occuped_space->toPlainText().toInt(),
        this->ui->text_exit_cars->toPlainText().toInt(),
        this->ui->text_tarif->toPlainText()
    );
    close();
}


void Form::on_btn_cancel_clicked()
{
    close();
}

