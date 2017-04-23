#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QGraphicsScene>

#include "grid.h"

=======
>>>>>>> multi_dev

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

<<<<<<< HEAD
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent* event);
private:
    void paintGrid(Grid*);
    Ui::MainWindow *ui;
    const int SCENE_WIDTH = 1000;


public slots:
    void initGame();
=======
private:
    Ui::MainWindow *ui;
>>>>>>> multi_dev
};

#endif // MAINWINDOW_H
