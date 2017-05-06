#ifndef BEINGWINDOW_H
#define BEINGWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QLineEdit>
#include "animal.h"
#include "predator.h"
#include "herbivorous.h"
namespace Ui {
class BeingWindow;
}

class BeingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeingWindow(QWidget *parent = 0);
    ~BeingWindow();
    void initWindow(Being*); // initialize window information
private:
    Ui::BeingWindow *ui;
    void lineInfoChange(QLineEdit*, const QString&);
};

#endif // BEINGWINDOW_H
