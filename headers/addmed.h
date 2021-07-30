#ifndef ADDMED_H
#define ADDMED_H

#include <QDialog>
#include "medicine.h"

namespace Ui {
class AddMed;
}

class AddMed : public QDialog
{
    Q_OBJECT

public:
    explicit AddMed(QWidget *parent = nullptr);
    ~AddMed();

     Medicine med;
     bool is_added = false;

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddMed *ui;
};

#endif // ADDMED_H
