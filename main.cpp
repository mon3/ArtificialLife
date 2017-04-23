#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
