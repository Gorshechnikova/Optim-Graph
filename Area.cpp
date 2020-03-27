#include "Area.h"
#include <vector>

bool Area::IsInArea(std::vector<double> x, double eps) {
	for (int i = 0; i < dimension; ++i)
		if ((border[2 * i] - eps > x[i]) || (border[2 * i + 1] + eps < x[i]))
			return false;
	return true;
}

int Area::GetDimension() {
	return dimension;
}

std::vector<double> Area::GetBorder() {
	return border;
}
