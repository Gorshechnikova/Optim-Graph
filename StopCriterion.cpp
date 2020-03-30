#include "StopCriterion.h"
#include <vector>
#include "funcs.h"

//для итерационного метода

bool nabla::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (norm_2(grad) < eps_2)
		return true;
	return false;
};

bool coord::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	std::vector<double> x(x0.size());
	for (unsigned int i = 0; i < x.size(); ++i)
		x[i] = x1[i] - x0[i];
	if (norm_2(x) < eps_2)
		return true;
	return false;
};

bool value::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
    if (qFabs((f1 - f0)/f1) < eps)
		return true;
	return false;
};

//для стохастического метода

//для прибавления к числу итераций с последнего улучшения:
//возвращает 0, если произошло улучшение (+ сделать сброс числа таких итераций)
//возвращает 1, если улучшения не было (прибавить 1 к числу таких итераций)
bool n_iter::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
	if (f1 < f0)
		return false;
	return true;
}

bool last_improv::stop(std::vector<double> x0, std::vector<double> x1, double f0, double f1, std::vector<double> grad) {
    if (qFabs(f1-f0) < eps)
		return true;
	return false;
}

void StopCriterion::Set_eps(double epsil) {
	eps = epsil;
	eps_2 = eps * eps;
}

void StopCriterion::Set_n_hat(int n_h) {
	n_hat = n_h;
}

int StopCriterion::Get_n_hat() {
	return n_hat;
}
