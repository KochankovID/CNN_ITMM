//: ��������� ������������ ��� �����

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// ������ ������ ������ ��������� (� ��������� ��� ���)
#define Teach
#define OUT (X) std::cout << X;
#define NUMBER nums[j]

// �������
class Sign : public DD_Func
{
public:
	Sign() : DD_Func() {};
	double operator()(const double& x) {
		if (x <= 0) {
			return -1;
		}
		else {
			return 1;
		}
	}
	~Sign() {};
};

class SignD : public Sign
{
public:
	SignD() : Sign() {};
	double operator()(const double& x) {
		return 1;
	}
	~SignD() {};
};


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
	Sigm F(2.6);
	SigmD f(2.6);
	Sign FF;
	SignD ff;
	srand(time(0));
	// �������� ����� ���������
	Matrix<Weights<double>> W(1,10);
	for (int i = 0; i < 10; i++) {
		W[0][i] = Weights<double>(5, 3);
		for (int j = 0; j < W[0][i].getN(); j++) {
			for (int p = 0; p < W[0][i].getM(); p++) {
				W[0][i][j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
			}
		}
	}

	// �������� ����� ��� ������� ���� ����
	Weights<double> W1(1, 10);
	for (int j = 0; j < W1.getN(); j++) {
		for (int p = 0; p < W1.getM(); p++) {
			W1[j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
		}
	}
	Weights<double> W2(1, 10);
	for (int j = 0; j < W1.getN(); j++) {
		for (int p = 0; p < W1.getM(); p++) {
			W2[j][p] = (p % 2 ? ((double)rand() / RAND_MAX) : -((double)rand() / RAND_MAX));
		}
	}
	//cout << W;
	//cout << W1;
#ifdef Teach

	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	// �������� ��������� �������
	vector<Matrix<double>> Nums(10);

	// ������ ������� ������� ���� ����
	Matrix<double> m(1,10);

	// ��������� ������� ��������� �������
	ifstream TeachChoose;
	TeachChoose.open("TeachChoose.txt");
	for (int i = 0; i < Nums.size(); i++) {
		TeachChoose >> Nums[i];
	}
	TeachChoose.close();

	// �������� ����
	long int k = 800; // ���������� �������� ���������
	double summ; // ���������� �����
	double y; // ���������� ������ ����
	double y1; // ���������� ������ ����

	for (long int i = 0; i < k; i++) {
		Teacher.shuffle(nums, 10); // ��������� ������������������
		cout << i << endl;
		for (int j = 0; j < 10; j++) { // ���� ������� �� ��������� �������
			for (int u = 0; u < 3; u++) {
				for (int l = 0; l < 10; l++) { // ���� ������� �� ����
					summ = Neyron.Summator(Nums[NUMBER], W[0][l]); // ��������� ���������� �����
					m[0][l] = Neyron.FunkActiv(summ, F);
				}
				summ = Neyron.Summator(m, W1); // ��������� ���������� �����
				y = Neyron.FunkActiv(summ, F);
				summ = Neyron.Summator(m, W2);
				y1 = Neyron.FunkActiv(summ, F);
				if (NUMBER == 4) {
					W1.GetD() = Teacher.PartDOutLay(1, y);
					W2.GetD() = Teacher.PartDOutLay(0, y1);
				}
				else if(NUMBER == 5){
					W1.GetD() = Teacher.PartDOutLay(0, y);
					W2.GetD() = Teacher.PartDOutLay(1, y1);
				}
				else {
					W1.GetD() = Teacher.PartDOutLay(0, y);
					W2.GetD() = Teacher.PartDOutLay(0, y1);
				}
				Teacher.BackPropagation(W, W1);
				Teacher.BackPropagation(W, W2);
				for (int l = 0; l < 10; l++) {
					Teacher.GradDes(W[0][l], Nums[NUMBER], f, m[0][l]);
				}

				summ = Neyron.Summator(m, W1);
				Teacher.GradDes(W1, m, f, summ);
				summ = Neyron.Summator(m, W2);
				Teacher.GradDes(W2, m, f, summ);

				for (int l = 0; l < 10; l++) {
					W[0][l].GetD() = 0;
				}
				const double o = NUMBER * 0.1;
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
	vector<Matrix<double>> Tests(15);

	// ���������� �������� ������� �� �����
	ifstream Testsnums;
	Testsnums.open("Tests.txt");
	for (int i = 0; i < 14; i++) {
		Testsnums >> Tests[i];
	}

	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int j = 0; j < 14; j++) { // ���� ������� �� �������� �������
		for (int l = 0; l < 10; l++) { // ���� ������� �� ����
			summ = Neyron.Summator(Tests[j], W[0][l]); // ��������� ���������� �����
			m[0][l] = Neyron.FunkActiv(summ, F);
		}
		summ = Neyron.Summator(m, W1); // ��������� ���������� �����
		y = Neyron.FunkActiv(summ, F);
		summ = Neyron.Summator(m, W2); // ��������� ���������� �����
		y1 = Neyron.FunkActiv(summ, F);
		if (y > 0.9) {
			cout << "Test " << j << " : " << "recognized " << 4 << ' ' << y << endl;
		}
		if ((y1 > 0.9)) {
			cout << "Test " << j << " : " << "recognized " << 5 << ' ' << y << endl;
		}
	}

	// ����� ����� ����
	cout << endl << "Weights of network. First layer: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[0][i].Out();
		cout << endl;
	}
	cout << endl << "Weights of network. Second layer: " << endl;
	W1.Out();
	W2.Out();
	system("pause");
	return 0;

}