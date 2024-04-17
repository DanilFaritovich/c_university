#include "payparking.h"

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

PayParking::~PayParking(){};
