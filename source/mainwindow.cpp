#include "ui_mainwindow.h"

#include "../headers/mainwindow.h"
#include "../headers/addmed.h"
#include "../headers/medicine.h"
#include "../headers/medicineinfo.h"
#include "../headers/startwindow.h"

#include <QDate>
#include <QFile>

#include <iostream>
#include <fstream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);

    std::ifstream in("response.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream line_stream(line);
        Medicine med;
        std::string name;
        line_stream >> name;
        med.name = QString::fromStdString(name);

        int freq;
        line_stream >> freq;
        med.freq = (Frequency)freq;

        line_stream >> med.amount;

        std::string start_date_string;
        line_stream >> start_date_string;
        med.start_date = QDate::fromString(QString::fromStdString(start_date_string), "yyyy.MM.dd");

        int time;
        line_stream >> time;
        med.time = (Time)time;

        std::string comment;
        line_stream >> comment;
        med.comment = QString::fromStdString(comment);

        medicine.push_back(med);
    }

    ui->textBrowserInfoOfDay->setText("Meds will be shown here. Choose the date.");

    AddMedToCalendar(medicine);
    in.close();

    startWindow window;
    window.setModal(true);
    window.exec();
    window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    MedicineInfo window(medicine);
    window.setModal(true);
    window.exec();
    UpdateCalendar();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date) {
   QString response ="<b>" + date.toString("yyyy.MM.dd") + "</b>" + "<br>";
   if (medicine_calendar.find(date) != medicine_calendar.end()) {
       for (const auto& med : medicine_calendar[date]) {
           response += "\"" + med.name + "\"<br>";
       }
   }
   ui->textBrowserInfoOfDay->setText(response);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    std::ofstream of("response.txt");
    for (const auto& item : medicine) {
        of  << item << std::endl;
    }
    of.close();
}



void MainWindow::on_pushButton_2_clicked() {
    medicine.clear();
    medicine_calendar.clear();
    MainWindow::on_calendarWidget_clicked(ui->calendarWidget->selectedDate());
}

void MainWindow::on_pushButton_3_clicked() {
    AddMed window;
    Medicine med;
    med.start_date = ui->calendarWidget->selectedDate();

    window.setModal(true);
    window.exec();

    if (window.is_added) {
        med.freq = window.med.freq;
        med.amount = window.med.amount;
        med.name = window.med.name;
        med.time = window.med.time;
        med.comment = window.med.comment;

        medicine.push_back(med);
        AddMedToCalendar({med});
    }

    on_calendarWidget_clicked(ui->calendarWidget->selectedDate());
}

void MainWindow::AddMedToCalendar (const std::vector<Medicine>& medicines){
    for (const auto& med : medicines) {
        QDate current_date = med.start_date;
        for (int i = 0; i < med.amount; ++i) {
            medicine_calendar[current_date].push_back(med);
            switch (med.freq) {
                case 0: {
                    current_date = current_date.addDays(1);
                    break;
                }
                case 1: {
                    current_date = current_date.addDays(7);
                    break;
                }
            }
        }
        ui->calendarWidget->setGridVisible(true);
    }
}

void MainWindow::UpdateCalendar() {
    medicine_calendar.clear();
    AddMedToCalendar(medicine);
}


