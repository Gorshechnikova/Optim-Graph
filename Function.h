/*!
	������ ����� �������� ����������� �������� �������, ��������������� �� ����� ������������.
*/

#pragma once
#include "funcs.h"

class Function {
protected:
	double eps;
public:
    virtual ~Function() {};
	///��������� ��������� �������� � �������� �����
    virtual double eval(double x, double y) = 0;
	///��������� �������� �� ������ ����� ��������� ������� � �������� �����
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
	������� �������� ������� ������� ������� ������� �� �������� ������� � �������� ���������
	\param a,b ����������, �� ������� ���� �������
	\param eps_2 ����������� (� ��������)
	\func �������, ��� ������� ������ �������
	\return �����, � ������� ����������� ������� �� �������� ����������
*/
std::vector<double> Golden_ratio(std::vector<double> a, std::vector<double> b, double eps_2, Function * func);
