#include "../headers/changemed.h"
#include "ui_changemed.h"
#include <QMessageBox>

ChangeMed::ChangeMed(std::vector<Medicine>& meds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeMed),
    meds_(meds)
{

    ui->setupUi(this);

    ui->comboBoxFreq->addItem("Every day");
    ui->comboBoxFreq->addItem("Every week");


    ui->comboBoxTime->addItem("Morning");
    ui->comboBoxTime->addItem("Day");
    ui->comboBoxTime->addItem("Evening");

    for (auto& item : meds_) {
        ui->comboBoxName->addItem(item.name);
    }
    is_changed = false;

    QIcon icon(":/images/icon.png");
    setWindowIcon(icon);
}


ChangeMed::~ChangeMed() {
    delete ui;
}

const QString SAVED_FIELD_COLOR = "{ background-color: rgb(255, 255, 255); color: rgb(0,0,0);}";
const QString UNSAVED_FIELD_COLOR = "{ background-color: rgb(255, 0, 0); color: rgb(0,0,0);}";

void ChangeMed::on_comboBoxName_currentIndexChanged(int index) {
    ui->lineEditName->setText(meds_[index].name);
    ui->lineEditStartDate->setText(meds_[index].start_date.toString("yyyy.MM.dd"));
    ui->comboBoxFreq->setCurrentIndex(meds_[index].freq);
    ui->spinBoxAmount->setValue(meds_[index].amount);
    ui->comboBoxTime->setCurrentIndex(meds_[index].time);
    ui->lineEditCommetn->setText(meds_[index].comment);

    ui->lineEditName->setStyleSheet("QLineEdit " + SAVED_FIELD_COLOR);
    ui->lineEditStartDate->setStyleSheet("QLineEdit " + SAVED_FIELD_COLOR);
    ui->lineEditCommetn->setStyleSheet("QLineEdit " + SAVED_FIELD_COLOR);
    ui->comboBoxFreq->setStyleSheet("QComboBox " + SAVED_FIELD_COLOR);
    ui->comboBoxTime->setStyleSheet("QComboBox " + SAVED_FIELD_COLOR);
    ui->spinBoxAmount->setStyleSheet("QSpinBox " + SAVED_FIELD_COLOR);
}

void ChangeMed::on_pushButton_clicked() {
    if(is_changed) {
        meds_[ui->comboBoxName->currentIndex()].name =  ui->lineEditName->text();
        meds_[ui->comboBoxName->currentIndex()].start_date =  QDate::fromString(ui->lineEditStartDate->text(), "yyyy.MM.dd");
        switch (ui->comboBoxFreq->currentIndex()) {
            case 0: {
                 meds_[ui->comboBoxName->currentIndex()].freq = EVRD;
                 break;
            }
            case 1: {
                 meds_[ui->comboBoxName->currentIndex()].freq = EVRWK;
                 break;
            }
        }
        meds_[ui->comboBoxName->currentIndex()].amount =  ui->spinBoxAmount->value();
        switch (ui->comboBoxTime->currentIndex()) {
            case 0: {
                 meds_[ui->comboBoxName->currentIndex()].time = MORNING;
                 break;
            }
            case 1: {
                 meds_[ui->comboBoxName->currentIndex()].time = DAY;
                 break;
            }
            case 2: {
                meds_[ui->comboBoxName->currentIndex()].time = EVENING;
                break;
            }
        }
        meds_[ui->comboBoxName->currentIndex()].comment = ui->lineEditCommetn->text();
        is_changed = false;
        on_comboBoxName_currentIndexChanged(ui->comboBoxName->currentIndex());
    } else {
        QMessageBox msgBox;
        msgBox.setText("There is nothing to save");
        msgBox.exec();
    }
}

void ChangeMed::on_lineEditName_textChanged(const QString &arg1) {
    ui->lineEditName->setStyleSheet("QLineEdit " + UNSAVED_FIELD_COLOR);
    is_changed = true;
}

void ChangeMed::on_lineEditStartDate_textChanged(const QString &arg1) {
    is_changed = true;
    ui->lineEditStartDate->setStyleSheet("QLineEdit " + UNSAVED_FIELD_COLOR);
}

void ChangeMed::on_lineEditCommetn_textChanged(const QString &arg1) {
    is_changed = true;
    ui->lineEditCommetn->setStyleSheet("QLineEdit " + UNSAVED_FIELD_COLOR);
}

void ChangeMed::on_comboBoxFreq_currentIndexChanged(const QString &arg1)
{
    is_changed = true;
    ui->comboBoxFreq->setStyleSheet("QComboBox " + UNSAVED_FIELD_COLOR);
}


void ChangeMed::on_spinBoxAmount_valueChanged(const QString &arg1) {
    is_changed = true;
    ui->spinBoxAmount->setStyleSheet("QSpinBox " + UNSAVED_FIELD_COLOR);
}

void ChangeMed::on_comboBoxTime_currentIndexChanged(const QString &arg1) {
    is_changed = true;
    ui->comboBoxTime->setStyleSheet("QComboBox " + UNSAVED_FIELD_COLOR);
}

void ChangeMed::closeEvent(QCloseEvent *event) {
    if(is_changed) {
        bool is_saved = QMessageBox::question(
                    this,
                    tr("Unsaved chaneges"),
                    tr("There are unsaved chaneges."
                        "Do you want to save them?"),
                    tr("&No"), tr("&Yes"),
                    QString::null, 0, 1);
        if (is_saved) {
            on_pushButton_clicked();   
        }
    }
    close();
}

void ChangeMed::on_pushButtonDelete_clicked() {
    meds_.erase(meds_.begin() + ui->comboBoxName->currentIndex());
    if (meds_.empty()) {
        close();
    } else {
       ui->comboBoxName->removeItem(ui->comboBoxName->currentIndex());
    }
    is_changed = false;
}

