#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "medicine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event) override;

    void AddMedToCalendar (const std::vector<Medicine>& medicines);

    void UpdateCalendar();

private slots:
    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



private:
    Ui::MainWindow *ui;
    std::map<QDate, std::vector<Medicine>> medicine_calendar;
    std::vector<Medicine> medicine;
};

#endif // MAINWINDOW_H
