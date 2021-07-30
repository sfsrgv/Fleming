#ifndef MEDICINEINFO_H
#define MEDICINEINFO_H

#include <QDialog>
#include "medicine.h"

namespace Ui {
class MedicineInfo;
}

class MedicineInfo : public QDialog
{
    Q_OBJECT

public:
    explicit MedicineInfo(std::vector<Medicine>& med, QWidget *parent = nullptr);
    ~MedicineInfo();

private slots:
    void on_pushButton_clicked();

    void UpdateRespone();

private:
    std::vector<Medicine>& medicine;
    Ui::MedicineInfo *ui;
};

#endif // MEDICINEINFO_H
