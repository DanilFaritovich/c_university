#include "widget.h"
#include "string"

#include <QApplication>
#include <QPushButton>
#include <QObject>

using std::string;
using std::printf;
class PayParking{
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
