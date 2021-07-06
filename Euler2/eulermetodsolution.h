#ifndef EULERMETODSOLUTION_H
#define EULERMETODSOLUTION_H

#include <math.h>
#include <vector>

// Начальные данные
constexpr double pi = 3.14159265;
constexpr int V0 = 5;
constexpr int R = 1000;
constexpr double C = 0.000001;
constexpr double L = 0.001;
constexpr double w = 6000 * pi;

// Временной отрезок
constexpr double t0 = 0;
constexpr double t1 = 0.02;

// Структура для хранения временной сетки
struct Net
{
    std::vector<double> y;
    std::vector<double> I;
    size_t time;
    double tau;

    Net();
    Net(size_t step_count)
    {
        y = std::vector<double>(step_count + 1);
        I = std::vector<double>(step_count + 1);

        I[0] = 0;
        y[0] = 0;

        time = 0;
        tau = (t1 - t0) / step_count;
    }
};

// Класс решающий диффур колебательного контура
class EulerMetodSolution
{
  private:
    Net net;
    size_t step_count;

    double func();
    void stepper();

  public:
    EulerMetodSolution(size_t _step_count);

    void solver();
    size_t getStepCount() { return step_count; }
    double getTau() { return net.tau; }
    std::vector<double> getI() { return net.I; }
};

#endif // EULERMETODSOLUTION_H
