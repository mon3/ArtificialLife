#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->setParamsButton, SIGNAL(pressed()), this, SLOT(initGame()));
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    //todo: values validation

    if (ui->sceneSizeEdit->text().isEmpty())
        {
            qDebug("Please set correct grid parameters!");
        }
    else
    {
        int gridSize = ui->sceneSizeEdit->text().toInt();


    ParametersSet* set = ParametersSet::getInstance(gridSize);

    Grid* scene = new Grid();
    const QRect rec = QRect(0, 0, ParametersSet::SCENE_WIDTH, ParametersSet::SCENE_WIDTH);
    scene->setSceneRect(rec);
    timer = QSharedPointer<QTimer>(new QTimer);

    connect(ui->startButton, SIGNAL(pressed()), timer.data(), SLOT(start()));
    connect(ui->stopButton, SIGNAL(pressed()), timer.data(), SLOT(stop()));
    connect(timer.data(), SIGNAL(timeout()), scene, SLOT(updateGrid()));

    //test subjects
     Herbivorous* ex = new Herbivorous(3, 3);
     connectBeing(ex);
     scene->addItem(ex);
     set->addBeing(ex);

     ex = new Herbivorous(9, 8);
          connectBeing(ex);
          scene->addItem(ex);
          set->addBeing(ex);

     Plant* exp = new Plant(5, 5);
     connectBeing(exp);
     scene->addItem(exp);
     set->addBeing(exp);
     exp->setHitPoints(100);

     exp = new Plant(1, 3);
     connectBeing(exp);
     scene->addItem(exp);
     set->addBeing(exp);
     exp->setHitPoints(150);

     exp = new Plant(8, 8);
     connectBeing(exp);
     scene->addItem(exp);
     set->addBeing(exp);
     exp->setHitPoints(100);

     exp = new Plant(1, 1);
     connectBeing(exp);
     scene->addItem(exp);
     set->addBeing(exp);
     exp->setHitPoints(80);
    //test button
    connect(ui->testPushBUtton, SIGNAL(pressed()), scene, SLOT(updateGrid()));

    connect(ui->velocitySlider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    ui->graphicsView->setScene(scene);
    }

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

void MainWindow::connectBeing(Being *b)
{
    connect(b, SIGNAL(callWindow(Being*)), ParametersSet::getInstance(), SLOT(callWindow(Being*)));
    connect(ui->testPushBUtton, SIGNAL(pressed()), b, SLOT(updateBeing()));
    connect(timer.data(), SIGNAL(timeout()), b, SLOT(updateBeing()));
}


