#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QSharedPointer>
#include "grid.h"
#include "src/grid/beingitem.h"
#include "src/sugarscape/herbivorous.h"
#include "src/sugarscape/predator.h"
#include "src/shared/board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent* event);
private:
    Ui::MainWindow *ui;
    QSharedPointer<QTimer> timer;

    //change default name
    const float TIMER_TICKS = 1000.0f / 15.0f;
    float timerDelimiter;

    void connectBeing(BeingItem*);

public slots:
    void initGame();
    void sliderValueChanged(int val);
};

#endif // MAINWINDOW_H
