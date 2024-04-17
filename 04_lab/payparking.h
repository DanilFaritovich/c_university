#ifndef PAYPARKING_H
#define PAYPARKING_H

#include <string>
#include <QString>

using std::printf;
class PayParking
{
public:
    PayParking(QString name, QString place, int free_space_count, int occupied_space_count, int remove_cars_count, QString tarif);

    QString get_name(){return this->name;};
    QString get_place(){return this->place;};
    int get_free_space_count(){return this->free_space_count;};
    int get_occupied_space_count(){return this->occupied_space_count;};
    int get_remove_cars_count(){return this->remove_cars_count;};
    QString get_tarif(){return this->tarif;};

    void set_car();
    void remove_car();
    int get_free_spaces();

    ~PayParking();
private:
    QString name;
    QString place;
    int free_space_count;
    int occupied_space_count;
    int remove_cars_count;
    QString tarif;
};

#endif // PAYPARKING_H
