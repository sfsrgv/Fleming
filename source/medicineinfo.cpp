#include "../headers/medicineinfo.h"
#include "ui_medicineinfo.h"
#include "../headers/changemed.h"
#include<iostream>
#include <QMessageBox>

MedicineInfo::MedicineInfo(std::vector<Medicine>& med, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicineInfo),
    medicine(med)
{
    ui->setupUi(this);

    UpdateRespone();

    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);
}

MedicineInfo::~MedicineInfo()
{
    delete ui;
}

void MedicineInfo::on_pushButton_clicked() {
   if (medicine.empty()) {
      QMessageBox::warning(this, "No medicine", "There are no medicine to change :(", tr("&Ok"));
   } else {
       ChangeMed window(medicine);
       window.setModal(true);
       window.exec();
       UpdateRespone();
   }

}

void MedicineInfo::UpdateRespone() {
    QString response = "";
    for (const auto& item : medicine) {
        response += "\"" + item.name + "\" since " + item.start_date.toString("yyyy.MM.dd");
        response += " for " + QString::number(item.amount);
        switch (item.freq) {
            case 0: {
                response += " days";
                break;
            }
            case 1: {
                response += " weeks";
                break;
            }
        }
        response += " in the ";
        std::cout << item.time << "\n";
        switch (item.time) {
            case 0: {
                response += "morning ";
                break;
            }
            case 1: {
                response += "day ";
                break;
            }
            case 2: {
                response += "evening ";
                break;
            }
        }
        response += '\n';
    }
    if (response == "") {
        response += "There are no meds in your calendar";
    }

    ui->textBrowser->setText(response);
}
