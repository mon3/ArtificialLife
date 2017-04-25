#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <../parametersset.cpp>
#include <../grid.cpp>
#include <iostream>
//#include <../mainwindow.cpp>


class ArtifiacialLifeTests : public QObject
{
    Q_OBJECT

public:
    ArtifiacialLifeTests();

private Q_SLOTS:
    void initTestCase();
    // tests for ParametersSet::getGridSize()
    void testParametersSetCase1_data();
    void testParametersSetCase1();

    // tests for ParametersSet::getSeason
    void testParametersSetCase2_data();
    void testParametersSetCase2();

    // tests for Animal Class
    void testAnimal_data();
    void testAnimal();

    // tests for Grid data
    void testGrid_data();
    void testGrid();

    // tests for MainWindow Class (gui)
    void testMainWindow_data();
    void testMainWindow();

    // final test case
    void cleanupTestCase();

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

void ArtifiacialLifeTests::testParametersSetCase2_data()
{
    QTest::addColumn<Season>("first");
    QTest::addColumn<Season>("expected");

    ParametersSet paramsSet(200);
    paramsSet.setSeason(Season::winter);
    QTest::newRow("compare01") << paramsSet.getSeason() << Season::winter;
    paramsSet.setSeason(Season::spring);
    QTest::newRow("compare02") << paramsSet.getSeason() << Season::spring;
    paramsSet.setSeason(Season::summer);
    // exemplary test with failure
    QTest::newRow("compare03") << paramsSet.getSeason() << Season::spring;
    paramsSet.setSeason(Season::autumn);
    QTest::newRow("compare04") << paramsSet.getSeason() << Season::autumn;

}

void ArtifiacialLifeTests::testParametersSetCase1_data()
{
    QTest::addColumn<int>("first");
    QTest::addColumn<int>("expected");

    ParametersSet paramsSet(200);
    ParametersSet paramsSet1(300);
    ParametersSet paramsSet2(400);
    ParametersSet paramsSet3(500);

    QTest::newRow("compare01") << paramsSet.getGridSize()<< 200;
    // test with failure: values are not equal
    QTest::newRow("compare02") << paramsSet1.getGridSize()<< 250;
    QTest::newRow("compare03") << paramsSet2.getGridSize()<< 400;
    QTest::newRow("compare04") << paramsSet3.getGridSize()<< 500;

}


void ArtifiacialLifeTests::testParametersSetCase1()
{
    QFETCH(int, first);
    QFETCH(int, expected);
    QCOMPARE(first, expected);

}

void ArtifiacialLifeTests::testParametersSetCase2()
{
    QFETCH(Season, first);
    QFETCH(Season, expected);
    QCOMPARE(first, expected);

}

void ArtifiacialLifeTests::testGrid_data()
{
    // TODO: prepare exemplary and expected data for Grid class tests

}

void ArtifiacialLifeTests::testGrid()
{
// TODO: finish Grid class testing
//    ParametersSet *paramsSet = new ParametersSet(200);
//    Grid grid(paramsSet);

}

void ArtifiacialLifeTests::testAnimal_data()
{
  // TODO: prepare exemplary and expected data for Animal class tests
}

void ArtifiacialLifeTests::testAnimal()
{
    // TODO: Animal class tests for different types of animal
}

void ArtifiacialLifeTests::testMainWindow_data()
{
   // TODO:: prepare exemplary and expected data for gui tests
}

void ArtifiacialLifeTests::testMainWindow()
{
   // TODO: mainWindows tests
   // MainWindow mw;

}

//QTEST_MAIN(ArtifiacialLifeTests)
QTEST_APPLESS_MAIN(ArtifiacialLifeTests)


#include "tst_artifiaciallifetests.moc"
