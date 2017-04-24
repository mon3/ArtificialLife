#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <../parametersset.cpp>
#include <../grid.cpp>
//#include "../mainwindow.h"
#include "../ui_mainwindow.h"
//#include "../mainwindow.cpp"

class ArtifiacialLifeTests : public QObject
{
    Q_OBJECT

public:
    ArtifiacialLifeTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testParametersSet();
    void testAnimal();
    void testGrid();
    void testMainWindow();

};

ArtifiacialLifeTests::ArtifiacialLifeTests()
{
}

void ArtifiacialLifeTests::initTestCase()
{
    qDebug("STARTING unit tests...");
}

void ArtifiacialLifeTests::cleanupTestCase()
{
    qDebug("FINISHED unit tests...");
}

void ArtifiacialLifeTests::testParametersSet()
{
    ParametersSet paramsSet(200);
    paramsSet.setSeason(Season::winter);
    // one or separate ?
    QCOMPARE(paramsSet.getGridSize(), 200);
    QCOMPARE(paramsSet.getSeason(), Season::winter);
}

void ArtifiacialLifeTests::testGrid()
{
// TODO: finish Grid class testing
//    ParametersSet *paramsSet = new ParametersSet(200);
//    Grid grid(paramsSet);

}

void ArtifiacialLifeTests::testAnimal()
{
    // TODO: Animal class tests for different types of animal
}

void ArtifiacialLifeTests::testMainWindow()
{
   // TODO: mainWindows tests
   // MainWindow mw;

}

QTEST_MAIN(ArtifiacialLifeTests)

#include "tst_artifiaciallifetests.moc"
