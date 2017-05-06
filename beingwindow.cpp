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
    //clear old inf
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();

    ui->lineEdit_7->insert(QString::number(being->getLogX()));
    ui->lineEdit_8->insert(QString::number(being->getLogY()));
}
