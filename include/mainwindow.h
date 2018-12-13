#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "include/RjpClass/rjpshapeview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void updateWhenDataChange();
private slots:
    void openShapeFile();
private:
    Ui::MainWindow *ui;
    RjpShapeView* _shpView;
};

#endif // MAINWINDOW_H
