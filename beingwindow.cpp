#include "beingwindow.h"
#include "ui_beingwindow.h"

BeingWindow::BeingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BeingWindow)
{
    ui->setupUi(this);
    QGraphicsScene* s = new QGraphicsScene();
    ui->graphicsView->setScene(s);
}

BeingWindow::~BeingWindow()
{
    delete ui;
    qDebug() << "isCalled!";
}

void BeingWindow::initWindow(Being* being)
{
    ui->lineEdit_7->setText(QString(being->getLogX()));
    ui->lineEdit_8->setText(QString(being->getLogY()));
    qDebug() << "called!";
}
