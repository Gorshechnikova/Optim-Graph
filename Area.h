/*!
	¬ данном классе определ€ютс€ возможные заданные области, предоставл€емые пользователю на выбор.
*/

#pragma once
#include "funcs.h"

class Area {
protected:
	///–азмерность области
	int dimension;
	///√раница области
	std::vector<double> border;

public:
    virtual ~Area() {};
	Area(int n, std::vector<double> dot) : dimension(n), border(dot) {};
	/*!
		ѕровер€ет, находитс€ ли переданна€ точка в текущей области с заданной погрешностью.
		\param x ѕровер€ема€ точка
		\param eps «аданна€ погрешность
		\return 1, если точка внутри области; 0, иначе
	*/
	bool IsInArea(std::vector<double> x, double eps);
	int GetDimension();
	std::vector<double> GetBorder();
};

class RectArea : public Area {
protected:
public:
	RectArea(int n, std::vector<double> dot) : Area(n, dot) {};
};

class Area11 : public RectArea {
protected:
public:
	Area11(int n = 2, std::vector<double> dot = { 0, 3, 0, 3 }) : RectArea(n, dot) {};
};

class Area12 : public RectArea {
public:
	Area12(int n = 2, std::vector<double> dot = { 2, 5, 2, 5 }) : RectArea(n, dot) {};
};

class Area13 : public RectArea {
public:
    Area13(int n = 2, std::vector<double> dot = { -5, 5, -5, 5 }) : RectArea(n, dot) {};
};

class Area21 : public RectArea {
public:
	Area21(int n = 3, std::vector<double> dot = { 0, 3, 0, 3, 0, 3 }) : RectArea(n, dot) {};
};

class Area22 : public RectArea {
public:
	Area22(int n = 3, std::vector<double> dot = { 2, 5, 2, 5, 2, 5 }) : RectArea(n, dot) {};
};

class Area23 : public RectArea {
public:
	Area23(int n = 3, std::vector<double> dot = { -5, 5, -5, 5, -5, 5 }) : RectArea(n, dot) {};
};

class Area31 : public RectArea {
public:
	Area31(int n = 4, std::vector<double> dot = { 0, 3, 0, 3, 0, 3, 0, 3 }) : RectArea(n, dot) {};
};

class Area32 : public RectArea {
public:
	Area32(int n = 4, std::vector<double> dot = { 2, 5, 2, 5, 2, 5, 2, 5 }) : RectArea(n, dot) {};
};

class Area33 : public RectArea {
public:
	Area33(int n = 4, std::vector<double> dot = { -5, 5, -5, 5, -5, 5, -5, 5 }) : RectArea(n, dot) {};
};
