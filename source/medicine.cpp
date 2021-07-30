#include "../headers/medicine.h"

std::ofstream& operator<< (std::ofstream& of, const Medicine& item){
    of  << item.name.toStdString() << " "
        << item.freq << " "
        << item.amount << " "
        << item.start_date.toString("yyyy.MM.dd").toStdString() << " "
        << item.time << " "
        << item.comment.toStdString()
        << std::endl;
    return of;
}
