#ifndef MEDICINE_H
#define MEDICINE_H

#include <QString>
#include <QDate>

#include<fstream>


enum Frequency{EVRD = 0, EVRWK = 1};

enum Time{MORNING = 0, DAY = 1, EVENING = 2};

struct Medicine{
    QString name;
    Frequency freq;
    int amount;
    QDate start_date;
    Time time;
    QString comment;
};

std::ofstream& operator<< (std::ofstream& of, const Medicine& med);

#endif // MEDICINE_H
