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
    Grid* scene = new Grid(new ParametersSet(gridSize));
    const QRect rec = QRect(0, 0, SCENE_WIDTH, SCENE_WIDTH);
    scene->setSceneRect();
    ui->graphicsView->setScene(scene);
    paintGrid(scene);

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if(ui->graphicsView->scene())
        ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::showEvent(QShowEvent *)
{
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::paintGrid(Grid* scene)
{
    // Add the vertical lines first, paint them red
    //todo set params
    const int gridNumber = 20;
    int x = 0, y = 0;
    const int distance = SCENE_WIDTH / gridNumber;
    for (int i = -1; i < gridNumber; ++i ) {
        scene->addLine(x,0,x,SCENE_WIDTH, QPen(Qt::red));
        scene->addLine(0,y,SCENE_WIDTH,y, QPen(Qt::green));
        x+= distance;
        y+= distance;
    }
    ui->graphicsView->fitInView(scene->itemsBoundingRect());



}
