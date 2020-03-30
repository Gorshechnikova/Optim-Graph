#include <vector>
#include "funcs.h"
#include <cassert>

double norm_2(std::vector<double> x) {
	double ans{};
    for (size_t i = 0; i < x.size(); ++i)
		ans += x[i] * x[i];
	return ans;
}

double intersection(std::vector<double> x, std::vector<double> direction, std::vector<double> border)
{
	int dim = x.size();
	double alpha{}, opt_alpha = 100;
	for (int i = 0; i < dim; ++i) {
		if (direction[i] < 0)
			alpha = (border[i * 2] - x[i]) / direction[i];
		else if (direction[i] > 0)
			alpha = (border[i * 2 + 1] - x[i]) / direction[i];
		//else alpha = 0;
		if (alpha < opt_alpha)
			opt_alpha = alpha;
	}
	return opt_alpha;
}

std::vector<double> operator-(const std::vector<double>&a, const std::vector<double>&b)
{
	if (a.size() != b.size())
		assert("a.size() != b.size()"); 
	int dim = a.size();
	std::vector<double> c(dim);
    for (int i = 0; i < dim; ++i)
		c[i] = a[i] - b[i];
	return c;
}

std::vector<double> operator+(const std::vector<double>&a, const std::vector<double>&b)
{
	if (a.size() != b.size())
		assert("a.size() != b.size()");
	int dim = a.size();
	std::vector<double> c(dim);
    for (int i = 0; i < dim; ++i)
		c[i] = a[i] + b[i];
	return c;
}

std::vector<double> operator/(const std::vector<double>&a, const double &b)
{
	int dim = a.size();
	std::vector<double> c(dim);
    for (int i = 0; i < dim; ++i)
		c[i] = a[i] / b;
	return c;
}

std::vector<double> operator*(const double &b, const std::vector<double>&a)
{
	int dim = a.size();
	std::vector<double> c(dim);
    for (int i = 0; i < dim; ++i)
		c[i] = a[i] * b;
	return c;
}
