#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "processorthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    ProcessorThread processor;

    // QTimer class - to give time to respond to UI
    QTimer *tmrTimer;

    //ROI - region of interest
    QRect roi;

public slots:
    void UpdateGUI();
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // MAINWINDOW_H
