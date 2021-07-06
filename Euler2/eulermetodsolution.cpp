#include "eulermetodsolution.h"

// Конструктор класса решателя задачи
EulerMetodSolution::EulerMetodSolution(size_t _step_count) : net(_step_count)
{
    step_count = _step_count;
}

// Правая часть диффура у уравнения для Y
double EulerMetodSolution::func()
{
    double value = -net.y[net.time] / R / C - net.I[net.time] / L / C + V0 * cos(w * net.time * net.tau) / L / C / R;
    return value;
}

// Один шаг преобразования сетки
// подсчет значения для тока и вспомогательной переменной
// в нынешней ячейке сетки
void EulerMetodSolution::stepper()
{
    size_t time = net.time;
    double tau = net.tau;

    net.y[time + 1] = net.y[time] + tau * func();
    net.I[time + 1] = net.I[time] + tau * net.y[time];
}

// Обход по всей сетке
void EulerMetodSolution::solver()
{
    for (size_t i = 0; i < step_count; i++)
    {
        net.time = i;
        stepper();
    }
}
