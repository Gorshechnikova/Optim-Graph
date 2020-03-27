#include "Function.h"
#include <vector>

std::vector<double> Function::minus_eval_grad(std::vector<double> x) {
	std::vector<double> ans(x.size()), coordplush(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
		coordplush = x;
		coordplush[i] += eps*eps;
        ans[i] = -(eval(coordplush[0], coordplush[1]) - eval(x[0], x[1])) / (eps*eps);
	}
	return ans;
};

std::vector<double> Golden_ratio(std::vector<double> a, std::vector<double> b, double eps_2, Function * func) {
	while (norm_2(b - a) > eps_2) {
		std::vector<double> t = (b - a) / phi;
        double x1 = b[0] - t[0];
        double y1 = b[1] - t[1];
        double x2 = a[0] + t[0];
        double y2 = a[1] + t[1];
        if (func->eval(x1, y1) > func->eval(x2, y2))
        {
            a.push_back(x1);
            a.push_back(y1);
        }
        else {
            b.push_back(x2);
            b.push_back(y2);
        }
	}
	return ((a + b) / 2);
};

double function1::eval(double x, double y) {
    return (x - 2)*(x - 2)*(x - 2)*(x - 2) + (x - 2 * y)*(x - 2 * y);
};

double function2::eval(double x, double y) {
    return(exp(sin(x / 20 + y / 20)) + y);
};

double function3::eval(double x, double y) {
    return(sin(x)*cos(y));
};

void Function::Set_eps(double epsil) {
	eps = epsil;
}
