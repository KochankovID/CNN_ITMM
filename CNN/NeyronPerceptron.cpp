#include "NeyronPerceptron.h"



NeyronPerceptron::NeyronPerceptron()
{
}


double NeyronPerceptron::Summator(Matrix & a, const Weights & w)
{
	if ((a.getN() != w.getN()) || (a.getM() != w.getM())) {
		throw NeyronPerceptron::NeyronPerceptronExeption("Ќесовпадение размера матрицы весов и размера матрицы входных сигналов!");
	}
	double sum = 0;
	for (int i = 0; i < a.getN(); i++) {
		for (int j = 0; j < a.getM(); j++) {
			sum += a[i][j] * w[i][j];
		}
	}
	return sum;
}

double NeyronPerceptron::FunkActiv(const double & x, const double & a, double(*func)(const double &, const double &))
{
	return func(x,a);
}

NeyronPerceptron::~NeyronPerceptron()
{
}

double SingHopFunc(const double & x, const double & b)
{
	if (x >= b) {
		return 1;
	}
	return 0;
}

double Sigfunc(const double & x, const double & b)
{
	return 0.0;
}

double HyperTang(const double & x, const double &)
{
	return 0.0;
}
