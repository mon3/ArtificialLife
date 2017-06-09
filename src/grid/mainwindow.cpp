#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/evolalg/evolutionaryalg.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->miValue->setValidator(new QIntValidator(0,100, parent));
    //TODO: lambda > mi!!!
    ui->lambdaValue->setValidator(new QIntValidator(0,100, parent));

    connect(ui->setParamsButton, SIGNAL(pressed()), this, SLOT(initGame()));
}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame()
{
    //todo: values validation
    int mi=0, lambda = 0, maxIters = 1, reproductionType = 0, selectionType = 0;
    if (ui->sceneSizeEdit->text().isEmpty())
        {
            qDebug("Please set correct grid parameters!");
        }
    else
    {
        int gridSize = ui->sceneSizeEdit->text().toInt();

    if (ui->miValue->text().isEmpty())
    {
        qDebug("Please set parameter MI for EA!");
    }
    else
    {
        mi = ui->miValue->text().toInt();
    }


    if (ui->lambdaValue->text().isEmpty())
    {
        qDebug("Please set parameter LAMBDA for EA!");
    }
    else
    {
        lambda = ui->lambdaValue->text().toInt();
    }

    if (ui->Interpolation->isChecked())
    {
        reproductionType = 2;
    }
    else
    {
        reproductionType = 1;
    }

    selectionType = 1;


    EvolutionaryAlg* ea = new EvolutionaryAlg(mi, lambda, maxIters, reproductionType, selectionType);

    Grid* scene = new Grid(ea, 20, gridSize);
    const QRect rec = QRect(0, 0, ParametersSet::SCENE_WIDTH, ParametersSet::SCENE_WIDTH);
    scene->setSceneRect(rec);
    timer = QSharedPointer<QTimer>(new QTimer);

    connect(ui->startButton, SIGNAL(pressed()), timer.data(), SLOT(start()));
    connect(ui->stopButton, SIGNAL(pressed()), timer.data(), SLOT(stop()));
    connect(timer.data(), SIGNAL(timeout()), scene, SLOT(updateGrid()));




//    Populations p;
//    ea.initializePopulations(gridSize, std::get<0>(p), std::get<1>(p), 20);
//    auto& h = std::get<0>(p);
//    std::for_each(h.begin(), h.end(), [&](std::shared_ptr<Animal> h) -> void {
//       BeingItem* b = new BeingItem(h.get());
//       lambdaAdd(b);
//    });
//    std::for_each(std::begin(std::get<1>(p)), std::end(std::get<1>(p)), [&](std::shared_ptr<Animal> h) -> void {
//       BeingItem* b = new BeingItem(h.get());
//       lambdaAdd(b);
//    });
//

    connect(ui->testPushBUtton, SIGNAL(pressed()), scene, SLOT(updateGrid()));
    connect(ui->velocitySlider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    ui->graphicsView->setScene(scene);
    }

}

void MainWindow::sliderValueChanged(int val)
{
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

void MainWindow::connectBeing(BeingItem *b)
{
    connect(b, SIGNAL(callWindow(Being*)), ParametersSet::getInstance(), SLOT(callWindow(Being*)));
    connect(ui->testPushBUtton, SIGNAL(pressed()), b, SLOT(updateBeing()));
    connect(timer.data(), SIGNAL(timeout()), b, SLOT(updateBeing()));
}


