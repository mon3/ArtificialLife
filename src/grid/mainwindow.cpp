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
// nie trzeba else, bo zawsze ktorys bedzie zaznaczony

    if(ui->MiBestSelection->isChecked())
    {
        selectionType = 1;
    }
//    else if (ui->RouletteSelection->isChecked())
//    {
//        selectionType = 2;
//    }
//    else
//    {
//        selectionType = 3;
//    }



    EvolutionaryAlg* EA = new EvolutionaryAlg(mi, lambda, maxIters, reproductionType, selectionType);
    qDebug() << EA->getMi() << "\t" << EA->getLambda() << "\t" << EA->getReproductionType() << "\t" << EA->getSelectionType();

    ParametersSet* set = ParametersSet::getInstance(gridSize);
    Board* board = Board::getInstance(gridSize);
    QVector<Animal*> predatorIniPop;
    QVector<Animal*> herbivorousIniPop;

    Grid* scene = new Grid();
    const QRect rec = QRect(0, 0, ParametersSet::SCENE_WIDTH, ParametersSet::SCENE_WIDTH);
    scene->setSceneRect(rec);
    timer = QSharedPointer<QTimer>(new QTimer);

    connect(ui->startButton, SIGNAL(pressed()), timer.data(), SLOT(start()));
    connect(ui->stopButton, SIGNAL(pressed()), timer.data(), SLOT(stop()));
    connect(timer.data(), SIGNAL(timeout()), scene, SLOT(updateGrid()));


   auto lambdaAdd = [&] (BeingItem* b) -> void {
        board->addBeing(b->getBeing());
        connectBeing(b);
        scene->addItem(b);

    };

        //test subjects
    BeingItem* b = new BeingItem(new Herbivorous(1, 1));
    lambdaAdd(b);
    b = new BeingItem(new Herbivorous(3, 3));
    lambdaAdd(b);
    b = new BeingItem(new Herbivorous(4, 3));
    lambdaAdd(b);
    b = new BeingItem(new Predator(2, 1));
    lambdaAdd(b);
    b = new BeingItem(new Plant(5, 5));
    lambdaAdd(b);
//    ex = new Herbivorous(9, 8);
//    lambdaAdd(ex);
//    herbivorousIniPop.push_back(ex);

//    ex = new Herbivorous(4, 4);
//    lambdaAdd(ex);
//    herbivorousIniPop.push_back(ex);

//    Plant* pl = new Plant(4, 5);
//    lambdaAdd(pl);
//    pl = new Plant(2, 2);
//    lambdaAdd(pl);

//    pl = new Plant(4, 5);
//    lambdaAdd(pl);

//    pl = new Plant(7, 6);
//    lambdaAdd(pl);

//    pl = new Plant(8, 1);

//    lambdaAdd(pl);

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

void MainWindow::connectBeing(BeingItem *b)
{
    connect(b, SIGNAL(callWindow(Being*)), ParametersSet::getInstance(), SLOT(callWindow(Being*)));
    connect(ui->testPushBUtton, SIGNAL(pressed()), b, SLOT(updateBeing()));
    connect(timer.data(), SIGNAL(timeout()), b, SLOT(updateBeing()));
}


