#pragma once
#include "Matrix.h"

class NeyronPerceptron : public Matrix
{
public:
	// ������������ ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const int& i_, const int& j_);
	NeyronPerceptron(double** arr_, const int& i_, const int& j_);
	NeyronPerceptron(const NeyronPerceptron& copy);

	// ������ ������ ---------------------------------------------------------
	// �������� ������������ ������������ ������ �� ���� �������
	double Summator(double** arr_); 

	// ������� ��������� �������
	double FunkActiv(const double& x, double(*func)(const double&, const double&));

	// ���������� ------------------------------------------------------------
	~NeyronPerceptron();
};


// ������������� ������� ���������
// ������� ���������� ������
double SingHopFunc(const double& x, const double& b);

// ������������� �������
double Sigfunc(const double& x, const double& b);

// ��������������� �������
double HyperTang(const double& x, const double&);