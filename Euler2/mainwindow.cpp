#include "mainwindow.h"
#include "eulermetodsolution.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Отрисовка графика при нажатии на кнопку
void MainWindow::on_pushButton_clicked()
{
    // Задаем число шагов при
    size_t step_count = 1000000;
    EulerMetodSolution my_solution(step_count);

    // Решаем диффур
    my_solution.solver();

    std::vector<double> I = my_solution.getI();
    double tau = my_solution.getTau();

    // Нужны массивы типа QVector для отрисовки графика,
    // поэтому создаю массивы данного типа и перезаписываю
    // в них расчитанные в солвере значения
    QVector<double> x(step_count + 1);
    QVector<double> y(step_count + 1);

    for (size_t i = 0; i < step_count + 1; i++)
    {
        x[i] = i * tau;
        y[i] = I[i];
    }

    // очищаю график
    ui->widget->clearGraphs();
    // добавляю новый график
    ui->widget->addGraph();
    // устанавливаю данные для отрисовки
    ui->widget->graph(0)->setData(x, y);

    // задаю название осей
    ui->widget->xAxis->setLabel("time: t");
    ui->widget->yAxis->setLabel("Current: I");

    // задаю диапазон значений по оси Ох
    ui->widget->xAxis->setRange(t0, t1);

    // задаю диапазон значений по оси Оу
    double minY = y[0], maxY = y[0];
    for (size_t i = 1; i < step_count + 1; i++)
    {
        if (y[i] < minY)
            minY = y[i];
        if (y[i] > maxY)
            maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY);

    // отрисовываем
    ui->widget->replot();
}
