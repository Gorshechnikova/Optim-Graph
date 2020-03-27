#include "OptimizationMethod.h"
#include <vector>
#include <iostream>
#include <random>
#include "funcs.h"
#include <typeinfo>

const double min_fun = 9999;
const double step = 1e-10;
double delta = 0.1;
const int N_frag = 5;


std::vector<double> FletcherReevesCG::optimize(Area * area, Function * func, StopCriterion * criterion) {
	double eps_2 = eps * eps;
	int dim = area->GetDimension();
	std::vector<double> d0 = func->minus_eval_grad(y0), d1(dim), ans(dim);
	int j = 0;
	double lambda{};
    x.push_back(y0[0]);
    y.push_back(y0[1]);
	//starting point optimality check
	double norm0 = norm_2(d0), norm1{};
	if (norm0 < eps_2)
		return y0;

	while ((iter < limit_iter)) {
		std::vector<double> bord(dim), local_min_x(dim), test_dot(dim);
		double curr_eval_fanc{}, min_func = min_fun;
		d0 = func->minus_eval_grad(y0);

		//проверка на нахождение текущей точки на границе и направления градиента за область
		test_dot = y0 + step * d0;
		if (!area->IsInArea(test_dot, eps_2))
			return y0;
		//разбиение отрезка от начальной точки до границы по направлению градиента на n_frag точек (включая концы)
		std::vector<double> fragmentation1(dim), fragmentation2(dim);    //отрезок, на котором применяется золотое сечение
		lambda = intersection(y0, d0, area->GetBorder());   //лямбда для пересечения с границей
		for (int j = 1; j < N_frag; ++j) {                //N_frag - 1 отрезков, на которых применяется золотое се99чение
			for (int i = 0; i < dim; ++i) {
				bord[i] = y0[i] + lambda * d0[i];
				fragmentation1[i] = y0[i] + (bord[i] - y0[i])*(j - 1) / 5;
				fragmentation2[i] = y0[i] + (bord[i] - y0[i])*j / 5;
			}
			local_min_x = Golden_ratio(fragmentation1, fragmentation2, eps_2, func);
            curr_eval_fanc = func->eval(local_min_x[0], local_min_x[1]);

			if (min_func > curr_eval_fanc) {
				min_func = curr_eval_fanc;
				y1 = local_min_x;
                x.push_back(y1[0]);
                y.push_back(y1[1]);
			}
		}

		norm0 = norm_2(d0);
		std::vector<double> d = func->minus_eval_grad(y1);
		norm1 = norm_2(d);

		if (j < dim - 1) {
			double alpha = norm1 / norm0;
			for (int i = 0; i < dim; ++i) {
				d1[i] = func->minus_eval_grad(y1)[i] + alpha * d0[i];
				y0[i] = y1[i];
			}
			++j;
		}
		else {
            if (criterion->stop(x0, y1, func->eval(x0[0], x0[1]), func->eval(y1[0], y1[1]), func->minus_eval_grad(y1))) {
				return y1;
			}

			y0 = y1;
			x0 = y1;
			j = 0;
		}
		++iter;
	}
	return y0;
}

void OptimizationMethod::Set_eps(double epsil) {
	eps = epsil;
}

std::vector<double> Stochastic::optimize(Area * area, Function * func, StopCriterion * criterion) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//std::mt19937 gen(5);
	int dim = area->GetDimension();
	std::vector<double> border = area->GetBorder(), grad;
	std::uniform_real_distribution<> dis(0, 1);
	int n_h{};
	int n_hat = 1;
	if (typeid(*criterion) == typeid(n_iter))
		n_hat = dynamic_cast<n_iter*>(criterion)->Get_n_hat();
	double rand{};
    x.push_back(y0[0]);
    y.push_back(y0[1]);
    double curr_eval = func->eval(y0[0], y0[1]), new_eval{};
	while (iter < limit_iter && n_h < n_hat) {
		rand = dis(gen);         //этот rand для сравнения с вероятностью prob для выбора области
		if (rand > prob) {       //в качестве области выбирается вся область
			for (int i = 0; i < dim; ++i) {
				rand = dis(gen);     //этот rand для выбора рандомной точки в выбранной области для каждой координаты
				y1[i] = border[2 * i] + rand * (border[2 * i + 1] - border[2 * i]);
			}
		}
		else {                   //в качестве области выбирается куб "радиусом" delta
			for (int i = 0; i < dim; ++i) {
				rand = dis(gen);     //этот rand для выбора рандомной точки в выбранной области для каждой координаты
				if (y0[i] - delta < border[i * 2])
					y1[i] = border[2 * i] + rand * (y0[i] + delta - border[2 * i]);
				else if (y0[i] + delta > border[i * 2 + 1])
					y1[i] = y0[i] - delta + rand * (border[2 * i + 1] - y0[i] + delta);
				else
					y1[i] = y0[i] - delta + rand * 2 * delta;
			}
		}
		++iter;
        new_eval = func->eval(y1[0], y1[1]);
        x.push_back(y1[0]);
        y.push_back(y1[1]);
		if (typeid(*criterion) == typeid(n_iter)) {
			if (criterion->stop(y0, y1, curr_eval, new_eval, grad))      //пояснения работы в StopCriterion.cpp
				++n_h;
			else {
				n_h = 0;
				delta /= 2;
			}
		}
		else
		{
			if (criterion->stop(y0, y1, curr_eval, new_eval, grad))
				return y0;
		}
		if (new_eval < curr_eval) {
			y0 = y1;
			curr_eval = new_eval;
		}
	}
	return y0;
};

void OptimizationMethod::Set_x0y0y1(double x, double y) {
    x0.resize(0);
    y0.resize(0);
    y1.resize(0);
    x0.push_back(x);
    x0.push_back(y);
    y0 = x0;
    y1 = y0;
}

int OptimizationMethod::Get_iter() {
	return iter;
}

void OptimizationMethod::Set_limit_iter(int lim) {
	limit_iter = lim;
}

void OptimizationMethod::Set_prob(double p) {
	prob = p;
}
