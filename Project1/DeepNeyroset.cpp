#include "DeepNeyroset.h"
#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

Deepnetwork::Deepnetwork() : F(3.4), f(3.4), W(1, w1_count), W1(1, 10), m(1, w1_count)
{
	for (int i = 0; i < w1_count; i++) {
		W[0][i] = Weights<double>(5, 3);
	}
	for (int i = 0; i < 10; i++) {
		W1[0][i] = Weights<double>(1, w1_count);
	}
	// ���������� �����
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> W;
	fWeights >> W1;
	fWeights.close();
}

int Deepnetwork::Neyroset(double ooo[])
{
	Matrix<double> mii(ooo, 5, 3);

	for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
		summ = Neyron.Summator(mii, W[0][l]); // ��������� ���������� �����
		m[0][l] = Neyron.FunkActiv(summ, F);
	}
	for (int l = 0; l < 10; l++) { // ���� ������� �� ����
		summ = Neyron.Summator(m, W1[0][l]); // ��������� ���������� �����
		y[l] = Neyron.FunkActiv(summ, F); // ������ ������ l-���� ������� � ������ ������� ����
	}
	int max = 0;
	for (int l = 1; l < 10; l++) { // ��������� ����������� ����
		if (y[l] > y[max]) {
			max = l;
		}
	}
	return max;
}

Deepnetwork::~Deepnetwork()
{
}
