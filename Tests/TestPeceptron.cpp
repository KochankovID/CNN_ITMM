#include "TestPeceptron.h"
#include "Matrix.h"
#include "Weights.h"
#include <vector>
#include "Func.h"
#include <fstream>

// �������
class MyClass : public Func<int,double>
{
public:
	MyClass() : Func<int, double>() {};
	double operator()(const int& x) {
		if (x <= 0) {
			return -1.5;
		}
		else {
			return 1.5;
		}
	}
	~MyClass() {};
};

void TestPeceptron::testMetods()
{
	Matrix<int> Y(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Y[i][j] = 1;
		}
	}
	Weights<int> W(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			W[i][j] = 1;
		}
	}
	std::vector<int> T;
	std::vector<int> TT;
	for (int i = 0; i < 3; i++) {
		T.push_back(1);
		TT.push_back(2);
	}

	// ���� ����������
	test_(A.Summator(Y, W) == 9);
	test_(A.Summator(T, TT) == 6);

	MyClass O;
	// ���� ������� ���������
	test_(A.FunkActiv(A.Summator(Y, W), O) == 1.5);
	W[0][0] = -1000;
	test_(A.FunkActiv(A.Summator(Y, W), O) == -1.5);
}

void TestPeceptron::testExeptions()
{
	Matrix<double> Y(3, 2);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			Y[i][j] = 1;
		}
	}
	Weights<double> W(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			W[i][j] = 1;
		}
	}
	std::vector<double> T;
	std::vector<double> TT;
	for (int i = 0; i < 3; i++) {
		T.push_back(1);
		TT.push_back(2);
	}
	TT.pop_back();

	// ���� ���������� � ��������� ������
	try {
		B.Summator(Y, W);
		fail_("�� �������� ���������� ��������� ������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	// ���� ���������� � ��������� ��������
	try {
		B.Summator(T,TT);
		fail_("�� �������� ���������� ��������� ��������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

}

TestPeceptron::~TestPeceptron()
{
}
