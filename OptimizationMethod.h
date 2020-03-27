/*!
	������ ����� �������� ��� ������ ����������� ���������� �������� �������� ������� � �������� �������:
	- ������������ (����� ����� ����������� ���������� ��������-�����)
	- ��������������
*/

#pragma once
#include "Area.h"
#include "Function.h"
#include "StopCriterion.h"
#include "QVector"

class OptimizationMethod {
protected:
	std::vector<double> x0, y0, y1;
	int iter;
	double eps;
	int limit_iter;
public:
    std::vector<double> x;
    std::vector<double> y;
	OptimizationMethod(): iter(0) {};
    virtual ~OptimizationMethod() {};
	/*!
		������� ���������� �������� ������� � �����, � ������� �� �����������
		\param area ��������� �������, � ������� ����� ���������� �������
		\param func �������, ������� ������� ����� ����������
		\param criterion �������� ��������� ��� ���������� ������
		\return ����� �������� ������� � �������
    */
    ///����������� ��������� � ����������� ������� �����
    double prob;
    virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) = 0;
	int Get_iter();
    void Set_x0y0y1(double x, double y);
	void Set_eps(double epsil);
    void Set_limit_iter(int lim);
    void Set_prob(double p);
};

class FletcherReevesCG : public OptimizationMethod {
public:
    virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};

class Stochastic : public OptimizationMethod {

public:
    virtual std::vector<double> optimize(Area * area, Function * func, StopCriterion * criterion) override;
};
