#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "sswraper.h"

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
    updateModel();
    ui->mainView->setModel(&resultModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateModel()
{
    QStringList ssStdOut = ss.execute();
    resultModel.update((ssResultModel::SS_CONNECTION_TYPE)ui->socketTypesCombo->currentIndex(),
                       (ssResultModel::SS_IP_VERSION)ui->ipVersionsCombo->currentIndex(),
                       ssStdOut);
    //ui->mainView->resizeColumnsToContents();
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

void MainWindow::on_ipVersionsCombo_currentIndexChanged(int)
{
    updateModel();
}

void MainWindow::on_socketTypesCombo_currentIndexChanged(int)
{
    updateModel();
}
