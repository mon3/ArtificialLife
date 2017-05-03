#ifndef BEINGWINDOW_H
#define BEINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class BeingWindow;
}

class BeingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeingWindow(QWidget *parent = 0);
    ~BeingWindow();

private:
    Ui::BeingWindow *ui;
};

#endif // BEINGWINDOW_H
