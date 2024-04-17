#include "payparking.h"
#include <QMessageBox>

PayParking::PayParking(
    QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif
    ){
    this -> name = name;
    this -> place = place;
    this -> free_space_count = free_space_count;
    this -> occupied_space_count = occupied_space_count;
    this -> remove_cars_count = remove_cars_count;
    this -> tarif = tarif;
};

void PayParking::set_car(){
    if (this->free_space_count - this->occupied_space_count == 0){
        qInfo("set");
        QMessageBox msgBox;
        msgBox.setText("Внимательно прочтите!");
        msgBox.setInformativeText("Мест больше нет");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    this->occupied_space_count++;
}

void PayParking::remove_car(){
    if (this->occupied_space_count == 0){
        QMessageBox msgBox;
        msgBox.setText("Внимательно прочтите!");
        msgBox.setInformativeText("Машин и так нет");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    this->occupied_space_count--;
    this->remove_cars_count++;
}

int PayParking::get_free_spaces(){
    return this->free_space_count - this->occupied_space_count;
}

PayParking::~PayParking(){};
