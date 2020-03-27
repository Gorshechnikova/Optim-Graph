/*!
	Данный класс содержит определения различных критериев остановки для разных методов:
	- Итерационный метод:
 	 - Норма градиента меньше эпсилон
   	 - Норма разности двух соседних точек меньше эпсилон
	 - Модуль разности значений в двух соседних точках, деленной на значение в последней меньше эпсилон
	- Стохастический метод:
	 - Превышение числа итераций с последнего улучшения
	 - Модуль разности значений с последнего улучшения
*/

#pragma once
#include "funcs.h"

class StopCriterion {
protected:
	double eps;
	double eps_2;
    ///предел количества итераций с последнего улучшения
    int n_hat;
public:
    virtual ~StopCriterion() {};
	///Функция, осуществляющая проверку выбранного критерия остановки и возвращающая соответсвующее значение
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) = 0;
    void Set_eps(double epsil);
    void Set_n_hat(int n_h);
    int Get_n_hat();
};

class nabla : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class coord : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class value : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};

class n_iter : public StopCriterion {

public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;

};

class last_improv : public StopCriterion {
public:
	virtual bool stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) override;
};
