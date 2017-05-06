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
    ui->lineEdit_7->insert("std::string()");
    ui->lineEdit_8->insert(QString::number(being->getLogY()));
    qDebug() << "called!: x: " << being->getLogX() << " y: " << being->getLogY();
}
