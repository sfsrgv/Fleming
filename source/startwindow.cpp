#include "../headers/startwindow.h"
#include "ui_startwindow.h"

startWindow::startWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QPixmap m_logo_pic;
    m_logo_pic.load(":/images/logo_small.png");
    ui->label->setPixmap(m_logo_pic);
}

startWindow::~startWindow() {
    delete ui;
}

void startWindow::on_pushButton_clicked() {
    this->close();
}
