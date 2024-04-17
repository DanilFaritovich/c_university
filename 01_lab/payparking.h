#ifndef PAYPARKING_H
#define PAYPARKING_H
#include <string>

using std::string;
using std::printf;
class PayParking
{
public:
    PayParking(
        string name, string place, int free_space_count, string tarif
        ){
        this -> name = name;
        this -> place = place;
        this -> free_space_count = free_space_count;
        this -> occupied_space_count = 0;
        this -> remove_cars_count = 0;
        this -> tarif = tarif;
    };
    void set_car(){
        if (this->free_space_count - this->occupied_space_count == 0){
            printf("Мест больше нет");
            return;
        }
        this->occupied_space_count++;
    }

    void remove_car(){
        if (this->occupied_space_count == 0){
            printf("Машит нет");
            return;
        }
        this->occupied_space_count--;
        this->remove_cars_count++;
    }

    string get_name(){
        return this->name;
    }

    string get_place(){
        return this->place;
    }

    int get_free_space_count(){
        return this->free_space_count;
    }

    string get_tarif(){
        return this->tarif;
    }

    int get_occuped_count(){
        return this->occupied_space_count;
    }

    int get_remove_cars_count(){
        return this->remove_cars_count;
    }

    int get_free_spaces(){
        return this->free_space_count - this->occupied_space_count;
    }
    ~PayParking(){
    }
private:
    string name;
    string place;
    int free_space_count;
    int occupied_space_count;
    int remove_cars_count;
    string tarif;
};

#endif // PAYPARKING_H
