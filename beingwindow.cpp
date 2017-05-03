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
