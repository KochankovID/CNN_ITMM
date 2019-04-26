//: ��������� ������������ ��� �����

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// ������ ������ ������ ��������� (� ��������� ��� ���)
//#define Teach
#define OUT (X) std::cout << X;
#define NUMBER nums[j]

// �������
// ��������
class Sigm : public DD_Func
{
public:
	Sigm(const double& a_) : DD_Func(), a(a_) {};
	double a;
	double operator()(const double& x) {
		double f = 1;
		const double e = 2.7182818284;
		if (x >= 0) {
			for (int i = 0; i < a*x; i++)
			{
				f *= 1 / e;
			}
		}
		else {
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

using namespace std;

int main()
{
	// �������� �����������
	DD_Perceptron Neyron;

	// �������� ��������� ����
	DD_Leaning Teacher;
	Teacher.getE() = 0.09;

	// �������� ��������
	Sigm F(3.4);
	SigmD f(3.4);

	// ��������� ����� ��� ������ ��������� ��������
	srand(time(0));

	// ���������� �������� ������� ���� ���������
	const int w1_count = 100;

	// �������� ����� ���������
	Matrix<Weights<double>> W(1, w1_count);
	for (int i = 0; i < w1_count; i++) {
		W[0][i] = Weights<double>(5, 3);
		for (int j = 0; j < W[0][i].getN(); j++) {
			for (int p = 0; p < W[0][i].getM(); p++) {
				W[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}

	// �������� ����� ��� ������� ���� ����
	Matrix<Weights<double>> W1(1, 10);
	for (int i = 0; i < 10; i++) {
		W1[0][i] = Weights<double>(1, w1_count);
		for (int j = 0; j < W1[0][i].getN(); j++) {
			for (int p = 0; p < W1[0][i].getM(); p++) {
				W1[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
		W1[0][i].GetWBias() = (i % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
	}

	// ������ ������� ������� ���� ����
	Matrix<double> m(1, w1_count);

	double summ; // ���������� �����
	double y[w1_count]; // ���������� ������ ����

#ifdef Teach

	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	// �������� ��������� �������
	vector<Matrix<double>> Nums(10);

	// ��������� ������� ��������� �������
	ifstream TeachChoose;
	TeachChoose.open("TeachChoose.txt");
	for (int i = 0; i < Nums.size(); i++) {
		TeachChoose >> Nums[i];
	}
	TeachChoose.close();

	// �������� ����
	long int k = 70; // ���������� �������� ���������

	for (long int i = 1; i < k; i++) {
		Teacher.shuffle(nums, 10); // ��������� ������������������
		cout << i << endl;
		for (int j = 0; j < 10; j++) { // ���� ������� �� ��������� �������
			for (int u = 0; u < 3; u++) {
				for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
					summ = Neyron.Summator(Nums[NUMBER], W[0][l]); // ��������� ���������� �����
					m[0][l] = Neyron.FunkActiv(summ, F);
				}
				for (int l = 0; l < 10; l++) { // ���� ������� �� ����
					summ = Neyron.Summator(m, W1[0][l]); // ��������� ���������� �����
					y[l] = Neyron.FunkActiv(summ, F); // ������ ������ l-���� ������� � ������ ������� ����
				}
				for (int l = 0; l < 10; l++) { // ������ ������ ��� ��������� ����
					if (l == NUMBER) { // ���� ����� ������� ��������� � �������� �� ���� ������, �� ���������� ����� 1
						W1[0][l].GetD() = Teacher.PartDOutLay(1, y[l]); // ������ ������
					}
					else {// ���� ����� ������� ��������� � �������� �� ���� ������, �� ���������� ����� 1
						W1[0][l].GetD() = Teacher.PartDOutLay(0, y[l]); // ������ ������
					}
				}

				for (int l = 0; l < 10; l++) { // ��������������� ������ �� ������� ���� ���������
					Teacher.BackPropagation(W, W1[0][l]);
				}
				for (int l = 0; l < w1_count; l++) { // ���������� ������������ ������ �� ���� ��������� ������� ����
					Teacher.GradDes(W[0][l], Nums[NUMBER], f, m[0][l]);
				}
				for (int l = 0; l < 10; l++) { // ���������� ������������ ������ �� ���� ��������� ������� ����
					summ = Neyron.Summator(m, W1[0][l]);
					Teacher.GradDes(W1[0][l], m, f, summ);
				}
				for (int l = 0; l < w1_count; l++) { // ��������� ������ �������� 1 ����
					W[0][l].GetD() = 0;
				}
				Teacher.retract(W, 4);
				Teacher.retract(W1, 4);
			}
		}
	}

	// ��������� ����
	ofstream fWeights;
	fWeights.open("Weights.txt");
	fWeights << W;
	fWeights << W1;
	fWeights.close();

#else
	// ���������� �����
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> W;
	fWeights >> W1;
	fWeights.close();
#endif // Teach

	// �������� �������� �������
	vector<Matrix<double>> Tests(25);

	// ���������� �������� ������� �� �����
	ifstream Testsnums;
	Testsnums.open("Tests.txt");
	for (int i = 0; i < 24; i++) {
		Testsnums >> Tests[i];
	}
	double max;

	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int j = 0; j < 10; j++) { // ���� ������� �� �������� �������
		for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
			summ = Neyron.Summator(Tests[j], W[0][l]); // ��������� ���������� �����
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
		cout << "Test " << j << " : " << "recognized " << max << ' ' << y[max] << endl;
	}

	cout << "Test resilience:" << endl;
	for (int j = 10; j < 24; j++) { // ���� ������� �� �������� �������
		for (int l = 0; l < w1_count; l++) { // ���� ������� �� ����
			summ = Neyron.Summator(Tests[j], W[0][l]); // ��������� ���������� �����
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
		cout << "Test " << j << " : " << "recognized " << max << ' ' << y[max] << endl;
	}

	// ����� ����� ����
	cout << endl << "Weights of network. First layer: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[0][i].Out();
		cout << endl;
	}
	cout << endl << "Weights of network. First layer: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W1[0][i].Out();
		cout << endl;
	}
	system("pause");
	return 0;

}