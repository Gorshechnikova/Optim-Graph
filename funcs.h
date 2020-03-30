/*!
	Данный класс хранит функции и константу, применяемые методах различных классов.
*/

#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "QtMath"

///Константа, применяемая в золотом сечении
const double phi = 0.5 * (1.0 + sqrt(5.0));

///Возвращает норму переданного вектора в квадрате
double norm_2(std::vector<double> x);

/*!
	Пересекает вектор с границей области
	\param x Начало вектора
	\param grad Направление вектора
	\param border Границы текущей области
	\return Такое альфа, что 
	\f[
	\alpha = \argmin_\alpha (x+\alpha*grad)
	\f]
*/
double intersection(std::vector<double> x, std::vector<double> grad, std::vector<double> border);

std::vector<double> operator+(const std::vector<double>&a, const std::vector<double>&b);

std::vector<double> operator-(const std::vector<double>&a, const std::vector<double>&b);

std::vector<double> operator/(const std::vector<double>&a, const double &b);

std::vector<double> operator*(const double &b, const std::vector<double>&a);
