#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include "Area.h"
#include "Function.h"
#include "OptimizationMethod.h"
#include "funcs.h"
#include "StopCriterion.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int whatarea = 0;
    int whatfunction = 0;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double geomx;
        double geomy;
        std::vector <double> border;

private slots:
    void on_FR_clicked();

    void on_St_clicked();

    void on_area_currentIndexChanged(int index);
    
    void MakePlot(QCustomPlot * customPlot);

    void on_func_currentRowChanged(int currentRow);

//    void on_FRcrit_currentIndexChanged(int index);

    void on_Stcrit_currentIndexChanged(int index);

    void mouseClick(QMouseEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
