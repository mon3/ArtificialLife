#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <../parametersset.cpp>
#include <../grid.cpp>
#include <stdio.h>
//#include <../mainwindow.cpp>
//#include "../mainwindow.h"
//#include "../ui_mainwindow.h"
//#include "../mainwindow.cpp"



class ArtifiacialLifeTests : public QObject
{
    Q_OBJECT

public:
    ArtifiacialLifeTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testParametersSetData();
    void testParametersSet();

//    void testAnimalData();
    void testAnimal();

//    void testGridData();
    void testGrid();

//    void testMainWindowData();
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

void ArtifiacialLifeTests::testParametersSetData()
{
    QTest::addColumn<Season>("first");
    QTest::addColumn<Season>("expected");

    ParametersSet paramsSet(200);
    paramsSet.setSeason(Season::winter);
    std::cout<<paramsSet.getSeason();
    QTest::newRow("compare01") << paramsSet.getSeason() << Season::winter;
    paramsSet.setSeason(Season::spring);
    QTest::newRow("compare02") << paramsSet.getSeason() << Season::spring;
    paramsSet.setSeason(Season::summer);
    QTest::newRow("compare03") << paramsSet.getSeason() << Season::summer;
    paramsSet.setSeason(Season::autumn);
    QTest::newRow("compare04") << paramsSet.getSeason() << Season::autumn;

}





void ArtifiacialLifeTests::testParametersSet()
{
      QFETCH(Season, first);
      QFETCH(Season, expected);

      Season actual = first;
      QCOMPARE(actual, expected);

//    ParametersSet paramsSet(200);
//    paramsSet.setSeason(Season::winter);
//    // one or separate ?
//    QCOMPARE(paramsSet.getGridSize(), 200);
//    QCOMPARE(paramsSet.getSeason(), Season::winter);
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

//QTEST_MAIN(ArtifiacialLifeTests)
QTEST_APPLESS_MAIN(ArtifiacialLifeTests)


#include "tst_artifiaciallifetests.moc"
