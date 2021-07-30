#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>

namespace Ui {
class startWindow;
}

class startWindow : public QDialog
{
    Q_OBJECT

public:
    explicit startWindow(QWidget *parent = nullptr);
    ~startWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::startWindow *ui;
};

#endif // STARTWINDOW_H
