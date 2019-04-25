//: ��������� ������������ 4

#include "Perceptrons.h"
#include <vector>
#include <iostream>
#include <fstream>

#define Teach

// ������ ������ ������ ��������� (� ��������� ��� ���)
//#define Teach

// �������
class Sign : public II_Func
{
public:
	Sign() : II_Func(){};
	int operator()(const int& x) {
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
	II_Perceptron Neyron;

	// �������� ��������� ����
	II_Leaning Teacher;

	// �������� ��������
	Sign F;

	// �������� ����� �������
	Weights<int> Weight(5,3);
#ifdef Teach

	// ������������������ ����, �������� ��� ��������� ����������� ������������
	int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

	// �������� ��������� �������
	vector<Matrix<int>> Nums(10);

	// �������� ��������� �������
	// ��������� ������� ��������� �������
	ifstream TeachChoose;

	TeachChoose.open("TeachChoose.txt");
	for (int i = 0; i < Nums.size(); i++) {
		TeachChoose >> Nums[i];
	}
	TeachChoose.close();

	// �������� ����
	long int k = 167; // ���������� �������� ���������
	int summ; // ���������� �����
	int y; // ���������� ������ ����

	for (long int i = 0; i < k; i++) {
		Teacher.shuffle(nums, 10);
		for (int j = 0; j < 10; j++) {
			summ = Neyron.Summator(Nums[nums[j]], Weight); // ��������� ���������� �����
			y = Neyron.FunkActiv(summ, F); // ��������� ������ �������
			if (nums[j] != 4) {
				Teacher.WTSimplePerceptron(-1, y, Weight, Nums[nums[j]]);
			}
			else {
				Teacher.WTSimplePerceptron(1, y, Weight, Nums[nums[j]]);
			}
		}
	}

	// ��������� ����
	ofstream fWeights;
	fWeights.open("Weights.txt");
	fWeights << Weight;
	fWeights.close();

#else
	// ���������� �����
	ifstream fWeights;
	fWeights.open("Weights.txt");
	fWeights >> Weight;
	fWeights.close();

#endif // Teach
	// �������� �������� �������
	vector<Matrix<int>> Tests(14);


	// ���������� �������� ������� �� �����
	ifstream Testsnums;
	Testsnums.open("Tests.txt");
	for (int i = 0; i < 14; i++) {
		Testsnums >> Tests[i];
	}

	// �������� ������ ����
	cout << "Test network:" << endl;
	Neyron.FunkActiv(Neyron.Summator(Tests[0], Weight), F) == 1 ? cout << "Test " << 0 << " : " << "recognized 4" << endl : cout << "Test " << 0 << " : " << "doesn't recognized 4" << endl;

	// ����� �� ����� ���������� ������������ ����
	cout << "Test resilience:" << endl;
	for (int i = 1; i < 5; i++) {
		Neyron.FunkActiv(Neyron.Summator(Tests[i], Weight), F) == 1 ? cout << "Test " << i << " : " << "recognized 4" << endl : cout << "Test " << i << " : " << "doesn't recognized 4" << endl;
	}

	// ����� ����� ����
	cout << endl << "Weights of network: " << endl;
	Weight.Out();
	system("pause");
	return 0;
}
