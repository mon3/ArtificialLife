#include "mainwindow.h"
#include <QApplication>
<<<<<<< HEAD
=======
#include <QStyleFactory>
#include <iostream>
#include <QDebug>
>>>>>>> multi_dev

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
