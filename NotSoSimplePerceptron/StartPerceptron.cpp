//: ��������� ������������ ��� �����

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

// ������ ������ ������ ��������� (� ��������� ��� ���)
//#define Teach

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

using namespace std;
int main()
{
	// �������� �����������
	DD_Perceptron Neyron;

	// �������� ��������� ����
	DD_Leaning Teacher;
	Teacher.getE() = 1;

	// �������� ��������
	Sign F;

	// �������� ����� ���������
	vector<Weights<double>> W(10);
	for (int i = 0; i < 10; i++) {
		W[i] = Weights<double>(5, 3);
	}

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
	double summ; // ���������� �����
	double y; // ���������� ������ ����

	for (long int i = 0; i < k; i++) {
		Teacher.shuffle(nums, 10); // ��������� ������������������
		for (int j = 0; j < 10; j++) {
			for (int l = 0; l < 10; l++) {
				summ = Neyron.Summator(Nums[nums[j]], W[l]); // ��������� ���������� �����
				y = Neyron.FunkActiv(summ, F); // ��������� ������ �������
				if (nums[j] != l) { // ���� ������� ���� �� ��������� � �������� �� ���� ������ �� ��������� ����� ���� -1
					Teacher.WTSimplePerceptron(-1, y, W[l], Nums[nums[j]]);
				}
				else { // ���� ���������, �� ��������� ����� ���� 1
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

	// ����� �� ����� ���������� ������������ ����
	cout << "Test network:" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Neyron.FunkActiv(Neyron.Summator(Tests[i], W[j]), F) == 1)
				cout << "Test " << i << " : " << "recognized " << j << endl;
		}
	}

	// ����� �� ����� ���������� ������������ ����
	cout << "Test resilience:" << endl;
	for (int i = 10; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (Neyron.FunkActiv(Neyron.Summator(Tests[i], W[j]), F) == 1)
				cout << "Test " << i << " : " << "recognized " << j << endl;
		}
	}

	// ����� ����� ����
	cout << endl << "Weights of network: " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Weight " << i << "-th neyron's:" << endl;
		W[i].Out();
		cout << endl;
	}

	system("pause");
	return 0;

}

// ��������� ����� �������� � ��������� �������� �������� ����� 166,6666666666666
