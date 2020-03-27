/*!
	Данный класс содержит определения заданных функций, предоставляемых на выбор пользователю.
*/

#pragma once
#include "funcs.h"

class Function {
protected:
	double eps;
public:
    virtual ~Function() {};
	///Вычисляет выбранную ффункцию в заданной точке
    virtual double eval(double x, double y) = 0;
	///Вычисляет градиент со знаком минус выбранной функции в заданной точке
	std::vector<double> minus_eval_grad(std::vector<double> x);
	void Set_eps(double epsil);
};

class function1 : public Function {
public:
    virtual double eval(double x, double y) override;
};

class function2 : public Function {
public:
    virtual double eval(double x, double y) override;
};

class function3 : public Function {
public:
    virtual double eval(double x, double y) override;
};

/*!
	Методом золотого сечения находит минимум функции на заданном отрезке с заданной точностью
	\param a,b Промежуток, на котором ищем минимум
	\param eps_2 Погрешность (в квадрате)
	\func Функция, для которой ищется минимум
	\return Точку, в которой достигается минимум на заданном промежутке
*/
std::vector<double> Golden_ratio(std::vector<double> a, std::vector<double> b, double eps_2, Function * func);
