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
    ParametersSet::getInstance(gridSize);
    Grid* scene = new Grid();
    const QRect rec = QRect(0, 0, ParametersSet::SCENE_WIDTH, ParametersSet::SCENE_WIDTH);
    scene->setSceneRect(rec);
    timer = QSharedPointer<QTimer>(new QTimer);

    connect(ui->pushButton, SIGNAL(pressed()), timer.data(), SLOT(start()));
    connect(ui->pushButton_2, SIGNAL(pressed()), timer.data(), SLOT(stop()));
    connect(timer.data(), SIGNAL(timeout()), scene, SLOT(updateGrid()));

    //test button
    connect(ui->pushButton_5, SIGNAL(pressed()), scene, SLOT(updateGrid()));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    ui->graphicsView->setScene(scene);

}

void MainWindow::sliderValueChanged(int val)
{
    qDebug() << "called! " << val;
    timer->start(TIMER_TICKS / val);
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


