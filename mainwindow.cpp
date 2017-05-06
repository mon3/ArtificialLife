#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4, SIGNAL(pressed()), this, SLOT(initGame()));
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    //todo: values validation

//    const QRect rec = QRect(0, 0, 1000, 1000);
//    _grid->setSceneRect(rec);

//    ui->graphicsView->setScene(_grid);
//    ui->graphicsView->setSceneRect(rec);

    int gridSize = ui->lineEdit->text().toInt();
    Grid* scene = new Grid();
    const QRect rec = QRect(0, 0, ParametersSet::SCENE_WIDTH, ParametersSet::SCENE_WIDTH);
    scene->setSceneRect(rec);

    connect(ui->pushButton_5, SIGNAL(pressed()), scene, SLOT(updateGrid()));

    ui->graphicsView->setScene(scene);

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if(ui->graphicsView->scene())
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::showEvent(QShowEvent *)
{
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
}


