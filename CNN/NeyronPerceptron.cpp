#include "NeyronPerceptron.h"



NeyronPerceptron::NeyronPerceptron() : Matrix()
{
}

NeyronPerceptron::NeyronPerceptron(const int & i_, const int & j_) : Matrix(i_, j_)
{
}

NeyronPerceptron::NeyronPerceptron(double ** arr_, const int & i_, const int & j_) : Matrix(arr_, i_, j_), step(step_)
{
}

NeyronPerceptron::NeyronPerceptron(const NeyronPerceptron & copy) : Matrix(copy)
{
}

double NeyronPerceptron::Summator(double ** arr_)
{
	return 0.0;
}

double NeyronPerceptron::FunkActiv(const double & x, double(*func)(const double &, const double &))
{
	return 0.0;
}

double SingHopFunc(const double & x, const double & b)
{
	return 0.0;
}

double Sigfunc(const double & x, const double & b)
{
	return 0.0;
}

double HyperTang(const double & x, const double &)
{
	return 0.0;
}
