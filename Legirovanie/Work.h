#pragma once
#include <vector>

class my_decision
{
	double k1, k2, k3, k4;
	
	double y0, stepX, x0, xl, yl, new_y0, new_yl, new_x0, new_xl;
	double delta, Ld, F0, nd, N0;
	int points;

public:
	std::vector<double> alpha, betta;

	std::vector<double> psi;

	double mua, va, mub, vb;

	my_decision(double step, double my_y0, double my_x0, double my_yl, double my_xl, double e, double Nd, double _delta, int num);

	my_decision() {}

	double funcAlpha(double x, double y, double _y0);

	double funcBetta(double x, double y, double alpha, double _y0);

	void progonka(std::vector<double>& x, std::vector<double>& y, std::vector<double> vecy0);

	void control(std::vector<double>& x, std::vector<double>& y);

	void SetY0(std::vector<double>& y, std::vector<double>& x);

	double Norma(std::vector<double> y, std::vector<double> y0);

	void Y_obr(std::vector<double>& x, std::vector<double>& y);

	double func(double x, double y, double vy, double my_y0);

	double funcQ(double y0);

	double funcR(double y0);

	void Eyler(std::vector<double>& x, std::vector<double>& vec1, int function, std::vector<double> vecy0);
};
