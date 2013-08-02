#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "sswraper.h"
#include "ssresultmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QTimer refreshTimer;
    ssWraper ss;
    ssResultModel resultModel;

private slots:
    void updateModel();
    void on_refreshTimeSpin_valueChanged(int arg1);
    void on_ipVersionsCombo_currentIndexChanged(int index);
    void on_socketTypesCombo_currentIndexChanged(int index);
};

#endif // MAINWINDOW_H
