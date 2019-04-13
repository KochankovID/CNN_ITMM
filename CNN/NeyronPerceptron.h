#pragma once
#include "Matrix.h"
#include "Weights.h"

class NeyronPerceptron
{
public:
	// ������������ ----------------------------------------------------------
	NeyronPerceptron();
	NeyronPerceptron(const NeyronPerceptron& copy) = delete; // ������ �����������

	// ������ ������ ---------------------------------------------------------
	// �������� ������������ ������������ ������ �� ���� �������
	double Summator(Matrix& a, const Weights& w);

	// ������� ��������� �������
	double FunkActiv(const double& x, const double& a, double(*func)(const double&, const double&));

	// ���������� ���������� -------------------------------------------------
	NeyronPerceptron& operator= (const NeyronPerceptron& copy) = delete; // ������ �����������
	friend std::ostream& operator<<(std::ostream& out, const NeyronPerceptron& mat) = delete; // ������ ������ � �����
	friend std::istream& operator>>(std::istream& out, NeyronPerceptron& mat) = delete; // ������ ���������� �� ������

	// ���������� ------------------------------------------------------------
	~NeyronPerceptron();

	// ����� ���������� ------------------------------------------------------
	class NeyronPerceptronExeption : public std::runtime_error {
	public:
		NeyronPerceptronExeption(std::string str) : std::runtime_error(str) {};
		~NeyronPerceptronExeption() {};
	};
};


// ������������� ������� ���������
// ������� ���������� ������
double SingHopFunc(const double& x, const double& b);

// ������������� �������
double Sigfunc(const double& x, const double& b);

// ��������������� �������
double HyperTang(const double& x, const double&);