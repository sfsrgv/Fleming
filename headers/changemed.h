#ifndef CHANGEMED_H
#define CHANGEMED_H

#include <QDialog>
#include "medicine.h"

namespace Ui {
class ChangeMed;
}

class ChangeMed : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeMed(std::vector<Medicine>& meds, QWidget *parent = nullptr);
    ~ChangeMed();

     void closeEvent(QCloseEvent *event) override;

private slots:
    void on_comboBoxName_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_lineEditName_textChanged(const QString &arg1);

    void on_lineEditStartDate_textChanged(const QString &arg1);

    void on_lineEditCommetn_textChanged(const QString &arg1);

    void on_comboBoxFreq_currentIndexChanged(const QString &arg1);

    void on_spinBoxAmount_valueChanged(const QString &arg1);

    void on_comboBoxTime_currentIndexChanged(const QString &arg1);

    void on_pushButtonDelete_clicked();



private:
    Ui::ChangeMed *ui;
    std::vector<Medicine>& meds_;
    bool is_changed = false;
};

#endif // CHANGEMED_H
