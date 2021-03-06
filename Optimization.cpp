#include "pch.h"
#include "OptimizationMethod.h"
#include <typeinfo>
#include <cstdio>

const int lim = 100;

int main()
{
	int ind_func{}, ind_area{}, ind_stop{}, ind_method{};
	//char climit_iter[lim] = "", cprob[lim] = "", cn_hat[lim] = "", ceps[lim] = ""/*, * cinitial_point{}*/;
	int limit_iter{}/* = atoi(climit_iter)*/, n_hat{}/* = atoi(cn_hat)*/;
	double prob{}/* = atof(cprob)*/, eps{}/* = atof(cn_hat)*/;
	while (ind_func < 1 || ind_func > 5 || isdigit(ind_func)) {
		std::cout << "Choose 1 function from 5:" << std::endl
			<< "1. f(x,y) = (x - 2)^4 + (x - 2*y)^2" << std::endl
			<< "2. f(x,y) = exp(sin(x/20 + y/20)) + y" << std::endl
			<< "3. f(x,y) = sin(x)*cos(y)" << std::endl
			<< "4. f(x,y,z) = x*y*z" << std::endl
			<< "5. f(x,y,z,w) = x+y+z+w" << std::endl;
		std::cin >> ind_func;
	}
	Function * function = nullptr;
	Area * area = nullptr;

	switch (ind_func) {
	case 1:
	case 2:
	case 3: {
		while (ind_area < 1 || ind_area > 3 || isdigit(ind_area)) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area11; break;
		case 2: area = new Area12; break;
		case 3: area = new Area13; break;
		}
		break;
	}
	case 4: { function = new function4;
		while (ind_area < 1 || ind_area > 3 || isdigit(ind_area)) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area21; break;
		case 2: area = new Area22; break;
		case 3: area = new Area23; break;
		}
		break;
	}
	case 5: { function = new function5;
		while (ind_area < 1 || ind_area > 3 || isdigit(ind_area)) {
			std::cout << std::endl << "Choose 1 area from 3:" << std::endl
				<< "1. [0,3]*[0,3]*[0,3]*[0,3]" << std::endl
				<< "2. [2,5]*[2,5]*[2,5]*[2,5]" << std::endl
				<< "3. [-5,5]*[-5,5]*[-5,5]*[-5,5]" << std::endl;
			std::cin >> ind_area;
		}
		switch (ind_area) {
		case 1: area = new Area31; break;
		case 2: area = new Area32; break;
		case 3: area = new Area33; break;
		}
		break;
	}
	}
	switch (ind_func) {
	case 1: function = new function1; break;
	case 2: function = new function2; break;
	case 3: function = new function3; break;
	}

	StopCriterion * criterion = nullptr;

	//while (limit_iter <= 0 || atof(limit_iter)) {
	//	std::cout << std::endl << "Enter limit iteration: ";
	//	std::cin >> limit_iter;
	//	std::getline(std::cin, limit_iter);
	//}
	while (limit_iter <= 0) {
		char c[lim];
		std::cout << std::endl << "Enter limit iteration: ";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		gets_s(c, lim);
		limit_iter = atoi(c);
	}

	OptimizationMethod * method = nullptr;

	while (ind_method < 1 || ind_method > 2 || isdigit(ind_method)) {
		std::cout << std::endl << "Choose 1 method from 2:" << std::endl
			<< "1. Fletcher-Reeves CG" << std::endl
			<< "2. Stochastic method" << std::endl;
		std::cin >> ind_method;
	}
	if (ind_method == 1) {
		method = new FletcherReevesCG;
		while (ind_stop < 1 || ind_stop > 3 || isdigit(ind_stop)) {
			std::cout << std::endl << "Choose 1 stop criterion from 3:" << std::endl
				<< "1. || grad(f(x_k)) || < eps" << std::endl
				<< "2. || x_k - x_k-1 || < eps" << std::endl
				<< "3. || (f(x_k) - f(x_k-1))/f(x_k) || < eps" << std::endl;
			std::cin >> ind_stop;
		}
		switch (ind_stop) {
		case 1: criterion = new nabla; break;
		case 2: criterion = new coord; break;
		case 3: criterion = new value; break;
		}
	}
	else {
		method = new Stochastic;

		while (prob <= 0 || prob >= 1) {
			std::cout << std::endl << "Enter the probability of getting into a neighborhood of a point from 0 to 1: ";
			char c[lim];
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			gets_s(c, lim);
			prob = atof(c);
		}
		dynamic_cast<Stochastic*>(method)->Set_prob(prob);
		while (ind_stop < 1 || ind_stop > 2 || isdigit(ind_stop)) {
			std::cout << std::endl << "Choose 1 stop criterion from 1:" << std::endl
				<< "1. Reaching the iteration limit since last approach has improved" << std::endl
				<< "2. |f(x_k+j)-f(x_k)| < eps, j = min {m: f(x_k+m)<f(x_k)}" << std::endl;
			std::cin >> ind_stop;
		}
		switch (ind_stop) {
		case 1: {
			criterion = new n_iter;
			while (n_hat < 1) {
				std::cout << "Enter the limit of iterations from the last improvement: ";
				char c[lim];
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail());
				gets_s(c);
				n_hat = atoi(c);
			}
			dynamic_cast<n_iter*>(criterion)->Set_n_hat(n_hat);
			break;
		}
		case 2:
			criterion = new last_improv; break;
		}
	}
	method->Set_limit_iter(limit_iter);

	if (typeid(*criterion) == typeid(last_improv) || typeid(*method) == typeid(FletcherReevesCG)) {
		while (eps <= 0 || eps >= 1) {
			std::cout << std::endl << "Enter eps error: ";
			char c[lim];
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			gets_s(c, lim);
			eps = atof(c);
		}
		function->Set_eps(eps);
		method->Set_eps(eps);
		criterion->Set_eps(eps);
	}

	int dimen = area->GetDimension();
	std::vector <double> x(dimen);
	std::cout << std::endl << "Enter " << dimen << " values for initial point: ";
	for (int i = 0; i < dimen; ++i)
		std::cin >> x[i];
	while (!area->IsInArea(x, eps*eps)) {
		std::cout << "Enter values within the selected interval!" << std::endl;
		for (int i = 0; i < dimen; ++i) {
			char c[lim];
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "Enter " << i+1 << " in order coordinate of the initial point: ";
			gets_s(c);
			x[i] = atof(c);
			if (!x[i])
				if (strlen(c) == 2)
					x[i] = 0;
				else x[i] = lim;              //костыль, чтобы насильно выйти за пределы области для повторного запроса начальной точки
		}
	}
	method->Set_x0y0y1(x);

	std::vector<double> answer = method->optimize(area, function, criterion);
	std::cout << std::endl << std::endl << "Sought point: (";
	for (unsigned int i = 0; i < answer.size() - 1; ++i)
		std::cout << answer[i] << ", ";
	std::cout << answer[answer.size() - 1];
	std::cout << ")" << std::endl
		<< "Min value: " << function->eval(answer) << std::endl
		<< "Number of iterations: " << method->Get_iter() << std::endl;
	return 0;
}