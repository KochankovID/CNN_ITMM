#pragma once
#include <Windows.h>
#include "Perceptrons.h"
#include "CNNs.h"
#include <vector>
#include <iostream>
#include <fstream>

// C�������
class Sigm : public DD_Func
{
public:
	Sigm(const double& a_) : DD_Func(), a(a_) {};
	double a;
	double operator()(const double& x) {
		double f = 1;
		const double e = 2.7182818284;
		if (x >= 0) {
			if (x > 10000) {
				return 0.99999999;
			}
			for (int i = 0; i < a*x; i++)
			{
				f *= 1 / e;
			}
		}
		else {
			if (x < -10000) {
				return 0.00000001;
			}
			for (int i = 0; i < abs(a*x); i++)
			{
				f *= e;
			}
		}
		f++;
		return 1 / f;
	}
	~Sigm() {};
};

// ����������� ��������
class SigmD : public Sigm
{
public:
	SigmD(const double& a_) : Sigm(a_) {};
	double operator()(const double& x) {
		double f = 1;
		f = Sigm::operator()(x)*(1 - Sigm::operator()(x));
		return f;
	}
	~SigmD() {};
};

class Deepnetwork {
public:
	Deepnetwork();

	int Neyroset();

	~Deepnetwork();

private:

	// �������� �����������
	DD_Perceptron Neyron;

	// �������� CNN
	D_NeyronCnn NeyronCNN;

	// �������� ��������
	Sigm F;

	// ����������� ��������
	SigmD f;


	// ������ ������� �������
	static const int image_width = 28;
	static const int image_height = 28;

	// ������ �������� (���� �������)
	static const int filter_width = 5;
	static const int filter_height = 5;
	static const int filter1_width = 3;
	static const int filter1_height = 3;

	// ������ ������� �������� 
	static const int neyron_width = 100;
	static const int neyron_height = 4;
	static const int neyron1_width = 1;
	static const int neyron1_height = 50;

	// ���������� ��������
	static const int f1_count = 5; 
	static const int k = 5;
	static const int f2_count = f1_count * k;

	// ���������� ��������
	static const int w1_count = 120;
	static const int w2_count = 10;

	// ������� ������ ����
	Matrix<double> MATRIX_OUT;

	double summ; // ���������� �����
	double y[w2_count]; // ���������� ������ ����

	// �������� ����� �������� ������� ����
	std::vector<Filter<double>> FILTERS;

	// �������� ����� �������� ������� ����
	std::vector<Filter<double>> FILTERS1;

	// �������� ����� �������� ���� �����������
	Matrix<Weights<double>> WEIGHTS;

	// �������� ����� ��� ������� ���� �����������
	Matrix<Weights<double>> WEIGHTS1;


	// ������� ������ ����
	Matrix<double> IMAGE_OUT;

	// ������� �����������
	Matrix<double> IMAGE_1;
	std::vector< Matrix<double>> IMAGE_2;
	std::vector< Matrix<double>> IMAGE_3;
	std::vector< Matrix<double>> IMAGE_4;
	std::vector< Matrix<double>> IMAGE_5;

	// ������� ������ ���������� ����
	std::vector< Matrix<double>> IMAGE_2_D;
	std::vector< Matrix<double>> IMAGE_3_D;
	std::vector< Matrix<double>> IMAGE_4_D;
	std::vector< Matrix<double>> IMAGE_5_D;

	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

};