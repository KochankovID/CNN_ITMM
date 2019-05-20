//: ��������� ������������ ��� �����

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// ������ ������ ������ ��������� (� ��������� ��� ���)
#define Teach

// ��������
class Sigm : public DD_Func
{
public:
	Sigm(const double& a_) : DD_Func(), a(a_) {};
	double a;
	double operator()(const double& x) {
		double f = 1;
		const double e = 2.7182818284;
		for (int i = 0; i < a*x; i++)
		{
			f *= 1 / e;
		}
		f++;
		return 1 / f;
	}
	~Sigm() {};
};

// ����� ������ ������������� �������� � �������
int max(const double* arr, const int& length) {
	int m = 0;
	for (int i = 1; i < length; i++) {
		if (arr[i] > arr[m]) {
			m = i;
		}
	}
	return m;
};

using namespace std;

int main()
{
	// �������� �����������
	DD_Perceptron Neyron;

	// �������� ��������� ����
	DD_Leaning Teacher;
	Teacher.getE() = 1;

	// �������� ��������
	Sigm F(5.7);

	// �������� ����� ���������
	vector<Weights<double>> W(10);
	for (int i = 0; i < 10; i++) {
		W[i] = Weights<double>(5, 3);
	}

	double summ; // ���������� �����
	int y; // ���������� ������ ����
	double Outs[10] = { 0,1,2,0 };// ������ ������� ����
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
	long int k = 167; // ���������� �������� ���������

	for (long int i = 0; i < k; i++) {
		Teacher.shuffle(nums, 10); // ��������� ������������������
		for (int j = 0; j < 10; j++) { // ������ �� ��������� �������
			for (int l = 0; l < 10; l++) { // ������ �� ���� �������� ����
				summ = Neyron.Summator(Nums[nums[j]], W[l]); // ��������� ���������� �����
				y = Neyron.FunkActiv(summ, F); // ��������� ������ �������
				if (nums[j] != l) {
					// ���� ����� �������� ������� �� ��������� � ������� ������, �� ��������� ����� 0
					Teacher.WTSimplePerceptron(0, y, W[l], Nums[nums[j]]);
				}
				else {
					// ���� ����� �������� ������� ��������� � ������� ������, �� ��������� ����� 1
					Teacher.WTSimplePerceptron(1, y, W[l], Nums[nums[j]]);
				}
			}
		}
	}

	// ��������� ����
	ofstream fWeights;
	fWeights.open("Weights.txt");
	for (int i = 0; i < 10; i++) {
		fWeights << W[i];
	}
	fWeights.close();

#else
	// ���������� �����
	ifstream fWeights;
	fWeights.open("Weights.txt");
	for (int i = 0; i < 10; i++) {
		fWeights >> W[i];
	}
	fWeights.close();
#endif // Teach

	// �������� �������� �������
	vector<Matrix<double>> Tests(20);

	// ���������� �������� ������� �� �����
	ifstream Testsnums;
	Testsnums.open("Tests.txt");
	for (int i = 0; i < 20; i++) {
		Testsnums >> Tests[i];
	}

	// ����� �� ����� ���������� ������������ ���� �� ��������� �������
	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			summ = Neyron.Summator(Tests[i], W[j]); // ��������� ���������� �����
			Outs[j] = Neyron.FunkActiv(summ, F);
		}
		y = max(Outs, 10);
		// ����� ����������� �� �����
		cout << "Test " << i << " : " << "recognized " << y << endl;
	}

	// ����� �� ����� ���������� ������������ ���� �� �������� �������
	cout << "Test resilience:" << endl;
	for (int i = 10; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			summ = Neyron.Summator(Tests[i], W[j]); // ��������� ���������� �����
			Outs[j] = Neyron.FunkActiv(summ, F);
		}
		y = max(Outs, 10);
		// ����� ����������� �� �����
		cout << "Test " << i << " : " << "recognized " << y << endl;
	}

	// ����� ����� ���� �� �����
	cout << endl << "Weights of network: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[i].Out();
		cout << endl;
	}

	system("pause");
	return 0;

}