#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGroupBox"
#include "QSpinBox"
#include "QDoubleSpinBox"
#include "QMouseEvent"
#include "QTextBrowser"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mousePos(QMouseEvent*)));
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mouseClick(QMouseEvent*)));
    ui->Stoch->setEnabled(false);
    ui->limit_iter->setValue(1000);
    ui->FReps->setValue(0.001);
    ui->Stepsloc->setValue(0.1);
    ui->lim_iter_last->setValue(500);
    ui->Steps->setValue(0.001);
//    method->Set_eps(ui->FReps->value());
//    function->Set_eps(ui->FReps->value());
//    method->Set_limit_iter(ui->limit_iter->value());
    ui->func->addItem("f(x,y) = (x-2)^4 + (x-2*y)^2");
    ui->func->addItem("f(x,y) = exp(sin(x/20 + y/20)) + y");
    ui->func->addItem("f(x,y) = sin(x)*cos(y)");
    ui->area->addItem("[0,3]*[0,3]");
    ui->area->addItem("[2,5]*[2,5]");
    ui->area->addItem("[-5,5]*[-5,5]");
    ui->FRcrit->addItem("||grad(f(x_k))|| < eps");
    ui->FRcrit->addItem("||x_k - x_k-1|| < eps");
    ui->FRcrit->addItem("||(f(x_k) - f(x_k-1))/f(x_k)|| < eps");
    ui->Stcrit->addItem("Дост. лимит итер. после посл. прибл.");
    ui->Stcrit->addItem("|f(x_k+j)-f(x_k)| < eps");
    MainWindow::MakePlot(ui->customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakePlot(QCustomPlot * customPlot)
{
    ui->customPlot->clearPlottables();

//    method->Set_limit_iter(ui->limit_iter->value());
//    if (ui->FRCG->isChecked())
//    {
//        function->Set_eps(ui->FReps->value());
//        method->Set_eps(ui->FReps->value());
//        criterion->Set_eps(ui->FReps->value());
//    }
//    else method->Set_prob(ui->Stepsloc->value());
//    if (typeid(*criterion) == typeid(n_iter))
//        criterion->Set_n_hat(ui->lim_iter_last->value());
//    else if (typeid(*criterion) == typeid(last_improv))
//    {
//        function->Set_eps(ui->Steps->value());
//        method->Set_eps(ui->Steps->value());
//        criterion->Set_eps(ui->Steps->value());
//    }

    // configure axis rect:
    //customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    Area * area;
    switch (whatarea) {
    case 0: area = new Area11; break;
    case 1: area = new Area12; break;
    case 2: area = new Area13; break;
    }
    border = area->GetBorder();
    delete area;
        colorMap->data()->setRange(QCPRange(border[0], border[1]), QCPRange(border[2], border[3])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    Function * function;
    switch (whatfunction) {
    case 0: function = new function1; break;
    case 1: function = new function2; break;
    case 2: function = new function3; break;
    }
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        z = function->eval(x, y);
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }
    delete function;

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();
    customPlot->yAxis->setTickLabelRotation(-90);
    ui->customPlot->replot();
}

void MainWindow::on_FR_clicked()
{
        ui->FRCG->setEnabled(true);
        ui->Stoch->setEnabled(false);

       // method = new FletcherReevesCG;
}

void MainWindow::on_St_clicked()
{
    ui->FRCG->setEnabled(false);
    ui->Stoch->setEnabled(true);

    //method = new Stochastic;
}

void MainWindow::on_area_currentIndexChanged(int index)
{
    whatarea = index;
    MakePlot(ui->customPlot);
}

void MainWindow::on_func_currentRowChanged(int currentRow)
{
    whatfunction = currentRow;
    MakePlot(ui->customPlot);
}

//void MainWindow::on_FRcrit_currentIndexChanged(int index)
//{
//    switch (index)
//    {
//        case 0: criterion = new nabla; break;
//        case 1: criterion = new coord; break;
//        case 2: criterion = new value; break;
//    }
//}

void MainWindow::on_Stcrit_currentIndexChanged(int index)
{
    switch (index)
    {
       case 0: {
        //criterion = new n_iter;
        ui->label_9->setEnabled(true);
        ui->lim_iter_last->setEnabled(true);
        ui->label_11->setEnabled(false);
        ui->Steps->setEnabled(false);
        break;
    }
       case 1: {
        //criterion = new last_improv;
        ui->label_9->setEnabled(false);
        ui->lim_iter_last->setEnabled(false);
        ui->label_11->setEnabled(true);
        ui->Steps->setEnabled(true);
        break;
    }
    }
}

void MainWindow::mouseClick(QMouseEvent* event)
{   
    OptimizationMethod * method;
    StopCriterion * criterion;
    Function * function;
    Area * area;

    switch (whatarea) {
    case 0: area = new Area11; break;
    case 1: area = new Area12; break;
    case 2: area = new Area13; break;
    }
    switch (whatfunction) {
    case 0: function = new function1; break;
    case 1: function = new function2; break;
    case 2: function = new function3; break;
    }
    if (ui->FR->isChecked())
    {
        method = new FletcherReevesCG;
        switch (ui->FRcrit->currentIndex()) {
            case 0: criterion = new nabla; break;
            case 1: criterion = new coord; break;
            case 2: criterion = new value; break;
        }
        function->Set_eps(ui->FReps->value());
        method->Set_eps(ui->FReps->value());
        criterion->Set_eps(ui->FReps->value());
    }
    else {
        method = new Stochastic;
        if (ui->Stcrit->currentIndex()) {
            criterion = new n_iter;
            criterion->Set_n_hat(ui->lim_iter_last->value());
        }
        else {
            criterion = new last_improv;
            function->Set_eps(ui->Steps->value());
            method->Set_eps(ui->Steps->value());
            criterion->Set_eps(ui->Steps->value());
        }
        method->Set_prob(ui->Stepsloc->value());
    }
    method->Set_limit_iter(ui->limit_iter->value());


    //тут добавить проверку на принадлежность области рисования
    ui->result->clear();
    ui->result->insertPlainText("Начальная точка: ");
    QString num;
    ui->customPlot->mouseMove(event);
    geomx = border[0] + (border[1]-border[0])*(double((event->x()) - 47.)/345);
    geomy = border[2] + (border[3]-border[2])*((-double((event->y()) - 372.))/358);
    if (geomx < border[0] || geomx > border[1] ||
            geomy < border[2] || geomy > border[3])
        close();
//    geomx = event->x();
//    geomy = event->y();
    num = QString::number(geomx);
    ui->result->insertPlainText(num);
    ui->result->insertPlainText(" ");
    num = QString::number(geomy);
    ui->result->insertPlainText(num);
    //ui->result->setText("\n");
//    ui->x_0->setValue(geomx);
//    ui->y_0->setValue(geomy);
//    opt.x_0[0] = ui->x_0->value();
//    opt.x_0[1] = ui->y_0->value();

    method->Set_x0y0y1(geomx, geomy);
    std::vector <double> answer = method->optimize(area, function, criterion);

    QVector <double> qx = QVector<double>(method->x.begin(), method->x.end());
    QVector <double> qy = QVector<double>(method->y.begin(), method->y.end());
    QCPCurve * graph = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
        //QCPCurve *pathGraph = ui->plot->addGraph();
    graph->setData(qx, qy);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 0), QBrush(Qt::red), 5));
    graph->setPen(QPen(Qt::gray, 2));
    QCPCurve * final = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QVector<double> argx, argy;
    argx = QVector<double>(answer[0]);
    argy = QVector<double>(answer[1]);
    final->setData(argx, argy);
    final->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, QPen(Qt::yellow, 3), QBrush(Qt::yellow), 12));
    final->setPen(QPen(QColor(120, 120, 120), 2));
    ui->customPlot->replot();
    ui->customPlot->QCustomPlot::removePlottable(graph);
    ui->customPlot->QCustomPlot::removePlottable(final);

    delete method;
    delete area;
    delete function;
    delete criterion;
}
