#include "beingwindow.h"
#include "ui_beingwindow.h"

BeingWindow::BeingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BeingWindow)
{
    ui->setupUi(this);
}

BeingWindow::~BeingWindow()
{
    delete ui;
}

void BeingWindow::initWindow(Being* being)
{
    //add being info

    //set new data
    lineInfoChange(ui->lineEdit_7, QString::number(being->getLogX()));
    lineInfoChange(ui->lineEdit_8, QString::number(being->getLogY()));
    lineInfoChange(ui->lineEdit_9, QString::number(being->getHitPoints()));

    //set specyfic type data
    Animal* a;
    if((a = qobject_cast<Animal*>(being)) != 0) {
        //add info spec for animal class


        //add info specyfic for sub-animal class
        if(a= qobject_cast<Predator*>(a))
            lineInfoChange(ui->lineEdit_11, "Predator");
        else
            lineInfoChange(ui->lineEdit_11, "Herbivorous");

    }
    else
    {
        lineInfoChange(ui->lineEdit_11, "Plant");
    }
}

void BeingWindow::lineInfoChange(QLineEdit* line, const QString& text)
{
    line->clear();
    line->insert(text);
}
