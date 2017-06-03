#ifndef BEINGWINDOW_H
#define BEINGWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QLineEdit>
#include "src/sugarscape/animal.h"
#include "src/sugarscape/predator.h"
#include "src/sugarscape/herbivorous.h"
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
