#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "grid.h"


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
    void paintGrid(Grid*);
    Ui::MainWindow *ui;



public slots:
    void initGame();
};

#endif // MAINWINDOW_H
