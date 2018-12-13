#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include "QString"

#include "include/RjpClass/rjpshapescommand.hpp"
#include "include/RjpClass/rjpshapes.h"
#include "include/RjpClass/rjpshapeview.h"

namespace drawp = rjpshapefile::drawpart;
namespace obp = rjpshapefile::obpart;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create global data and set the ob
    obp::ShapesObCommand* sobc =
            new obp::ShapesObCommandTemplate<MainWindow>
            (this, &MainWindow::updateWhenDataChange);
    drawp::SingletonShapes::getGlobalData()->setOb(sobc);

    // Set the central widget
    _shpView = new RjpShapeView(this);
    this->setCentralWidget(_shpView);

    // Set the button
    connect(ui->actionOpen,SIGNAL(triggered(bool)),
            this,SLOT(openShapeFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateWhenDataChange(){
    this->update();
    this->_shpView->update();
}

void MainWindow::openShapeFile(){
    QFileDialog dialog(this,tr("Open File"),"",tr("*.shp"));
    dialog.setFileMode(QFileDialog::ExistingFiles); // Open multi-files at one time
    QStringList tem_list;
    if (dialog.exec())
        tem_list = dialog.selectedFiles();
    else
        return;
    drawp::SingletonShapes::getGlobalData()->addShapes(tem_list);
    drawp::SingletonShapes::getGlobalData()->notify();
}
