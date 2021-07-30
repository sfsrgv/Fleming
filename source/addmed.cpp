#include "../headers/addmed.h"
#include "ui_addmed.h"

#include<iostream>
#include<QMessageBox>

AddMed::AddMed(QWidget *parent) : QDialog(parent), ui(new Ui::AddMed) {
    ui->setupUi(this);
    ui->comboBoxFreq->addItem("Every week");
    ui->comboBoxFreq->addItem("Every day");

    ui->comboBoxTime->addItem("Morning");
    ui->comboBoxTime->addItem("Day");
    ui->comboBoxTime->addItem("Evening");

    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);
}

AddMed::~AddMed() {
    delete ui;
}

void AddMed::on_pushButton_clicked() {
    if (ui->lineEditName->text() == ""){
        QMessageBox::warning(this, "Not all information", "Please, enter the name", tr("&Ok"));
    } else {
        if (ui->spinBox->value() == 0) {
            QMessageBox::warning(this, "Not all information", "Please, enter number of days/weeks", tr("&Ok"));
        } else {
            is_added = true;
            med.name = ui->lineEditName->text();
            switch (ui->comboBoxFreq->currentIndex()) {
                case 0: {
                     med.freq = EVRWK;
                     break;
                }
                case 1: {
                     med.freq = EVRD;
                     break;
                }
            }
            med.amount = ui->spinBox->value();
            switch (ui->comboBoxTime->currentIndex()) {
                case 0: {
                     med.time = MORNING;
                     break;
                }
                case 1: {
                     med.time = DAY;
                     break;
                }
                case 2: {
                    med.time = EVENING;
                    break;
                }
            }
            med.comment = ui->lineEditComment->text();
            close();
        }
    }
}
