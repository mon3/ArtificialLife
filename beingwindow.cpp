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
    lineInfoChange(ui->xLoc, QString::number(being->getLogX()));
    lineInfoChange(ui->yLoc, QString::number(being->getLogY()));
    lineInfoChange(ui->hpInfo, QString::number(being->getHitPoints()));

    //set specyfic type data
    Animal* a;
    if((a = qobject_cast<Animal*>(being)) != 0) {
        //add info spec for animal class
        lineInfoChange(ui->activity, QVariant::fromValue(a->getActivity()).toString());
        lineInfoChange(ui->speed, QString::number(a->getSpeed()));
        lineInfoChange(ui->eveSight, QString::number(a->getEveSight()));

        //add info specyfic for sub-animal class
        if(a= qobject_cast<Predator*>(a))
            lineInfoChange(ui->typeInfo, "Predator");
        else
            lineInfoChange(ui->typeInfo, "Herbivorous");

    }
    else
    {
        lineInfoChange(ui->typeInfo, "Plant");
    }
}

void BeingWindow::lineInfoChange(QLineEdit* line, const QString& text)
{
    line->clear();
    line->insert(text);
}
