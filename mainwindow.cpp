#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
    int refreshTime = ui->refreshTimeSpin->value();
    if (refreshTime) {
        refreshTimer.start(refreshTime*1000);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateModel()
{
    static int count = 0;
    qDebug() << ++count << " shot";
    refreshTimer.start();
}

void MainWindow::on_refreshTimeSpin_valueChanged(int value)
{
    if (value) {
        refreshTimer.start(value*1000);
    }
    else {
        refreshTimer.stop();
    }
}
