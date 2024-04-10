#include "pch.h"
#include "Work.h"
#include <algorithm>
using namespace std;

my_decision::my_decision(double step, double my_y0, double my_x0, double my_yl, double my_xl, double e, double Nd, double _delta, int num)
{
	y0 = my_y0;
	x0 = my_x0;
	xl = my_xl;
	yl = my_yl;
	delta = _delta;
	points = num;
	double T = 300, kb = 1.38064852e-23, qe = 1.6e-19, e0 = 8.86e-12;
	F0 = (kb * T) / qe;
	//F0 = 0.05;
	new_y0 = y0 / F0;
	new_yl = yl / F0;

	double _Nd = step;
	nd = Nd;
	N0 = _Nd / nd;
	Ld = sqrt((e * e0 * kb * T) / (qe * qe * _Nd));
	new_x0 = x0 / Ld;
	new_xl = xl / Ld;
	stepX = (new_xl) / points;

	psi = vector<double>(points + 1);
}

double my_decision::funcAlpha(double x, double y, double _y0)
{
	return y * y * funcQ(_y0) + 1;
}

double my_decision::funcBetta(double x, double y, double alpha, double _y0)
{
	return -alpha * funcR(_y0) + alpha * y * funcQ(_y0);
}

void my_decision::progonka(std::vector<double>& x, std::vector<double>& y, std::vector<double> vecy0)
{
	Eyler(x, y, 0, vecy0);
	Eyler(x, y, 1, vecy0);
}

void my_decision::control(std::vector<double>& x, std::vector<double>& y)
{
	x.clear();
	vector<double> vecy0, my_try;
	SetY0(y, x);
	my_try = y;
	double norma;
	int iter = 0;
	do
	{
		vecy0 = y;
		progonka(x, y, vecy0);
		norma = Norma(y, vecy0);
		iter++;
		if (iter > 100)
		{
			MessageBox(NULL, L"iter > 100", L"iter", NULL);
			break;
		}
	} while (norma > delta);
	//y = alpha;
	Y_obr(x, y);
}

void my_decision::SetY0(std::vector<double>& y, std::vector<double>& x)
{
	new_y0 = y0;
	new_yl = yl;
	y.push_back(new_y0);
	x.push_back(new_x0);
	for (int i = 1; i < points + 1; i++)
	{

		y.push_back(new_y0 + (new_yl - new_y0) * i / (points));
		x.push_back(new_xl * i / points);
	}
}

double my_decision::Norma(std::vector<double> y, std::vector<double> vecy0)
{
	double razn = 0.;

	if (y.size() != vecy0.size())
	{
		MessageBox(NULL, L"Error", L"error y y0", NULL);
		return 0.0;
	}

	for (int i = 0; i < points + 1; i++)
	{
		razn += (y[i] - vecy0[i]) * (y[i] - vecy0[i]);
	}
	return razn;
}

void my_decision::Y_obr(std::vector<double>& x, std::vector<double>& y)
{
	if (y.size() != x.size())
	{
		MessageBox(NULL, L"Error", L"error x y", NULL);
		return;
	}

	for (int i = 0; i < points + 1; i++)
	{
		x[i] *= Ld * 1e6;
		//y[i] *= F0;
	}
}

double my_decision::func(double x, double y, double vy, double my_y0)
{
	return nd * (1. - exp(-y));
}

double my_decision::funcQ(double y0)
{
	return -nd * exp(-y0);
}

double my_decision::funcR(double y0)
{
	return func(y0, y0, y0, y0) + funcQ(y0) * y0;
}


void my_decision::Eyler(std::vector<double>& x, std::vector<double>& vec1, int function, std::vector<double> vecy0)
{
	vector<double> y;

	if (function == 0)
	{
		alpha = vector<double>(points + 1);
		betta = vector<double>(points + 1);

		alpha[0] = 0.;
		betta[0] = y0;

		for (int i = 1; i <= points; i++)
		{
			alpha[i] = alpha[i - 1] + (alpha[i - 1] * alpha[i - 1] * funcQ(vecy0[i - 1]) + 1) * stepX;
			betta[i] = betta[i - 1] + (alpha[i - 1] * betta[i - 1] * funcQ(vecy0[i - 1]) - alpha[i - 1] * funcR(vecy0[i - 1])) * stepX;
		}
		vec1[points] = new_yl;
		psi[points] = (vec1[points] - betta[points]) / alpha[points];
	}
	else
	{
		for (int i = points - 1; i >= 0; i--)
		{
			psi[i] = psi[i + 1] - (funcR(vecy0[i + 1]) - funcQ(vecy0[i + 1]) * (alpha[i + 1] * psi[i + 1] + betta[i + 1])) * stepX;
		}

		vec1 = vector<double>(points + 1);
		for (int i = 0; i <= points; i++)
		{
			vec1[i] = alpha[i] * psi[i] + betta[i];
		}
	}
}
