#include "TestMatrix.h"
#include <iostream>
#include <fstream>

using namespace std;


void TestMatrix::testConstruktors()
{ 
	// ����������� �� ���������
	Matrix<int> R;
	test_(R.getN() == 0);
	test_(R.getM() == 0);

	// ����������� �������������
	double** t;
	t = new double*[2];
	t[0] = new double[2];
	t[1] = new double[2];

	t[0][0] = 0;
	t[0][1] = 1;
	t[1][0] = 2;
	t[1][1] = 3;

	Matrix<double> D(t, 2, 2);
	test_(D.getN() == 2);
	test_(D.getM() == 2);

	test_(D[0][0] == 0);
	test_(D[0][1] == 1);
	test_(D[1][0] == 2);
	test_(D[1][1] == 3);

	// ���������� ������������� ������ �������
	Matrix<int> G(2, 3);
	test_(G.getN() == 2);
	test_(G.getM() == 3);

	test_(G[0][0] == 0);
	test_(G[0][1] == 0);
	test_(G[0][2] == 0);
	test_(G[1][0] == 0);
	test_(G[1][1] == 0);
	test_(G[1][2] == 0);

	// ����������� �����������
	Matrix<double> P(D);
	test_(P.getN() == 2);
	test_(P.getM() == 2);

	test_(P[0][0] == 0);
	test_(P[0][1] == 1);
	test_(P[1][0] == 2);
	test_(P[1][1] == 3);
}

void TestMatrix::testMetods()
{
	// ��������� ���������� �����
	test_(A.getN() == 3);

	// ��������� ����������� ��������
	test_(A.getM() == 3);

	// ����� ��������� � ������� ���� �� ����
	double** t;
	t = new double*[2];
	t[0] = new double[2];
	t[1] = new double[2];

	t[0][0] = 0;
	t[0][1] = 1;
	t[1][0] = 2;
	t[1][1] = 3;

	test_(Matrix<double>::Max(t, 2, 2) == 3);

	// ����� ��������� � �������
	test_(A.Max() == 8);

	// ��������� ����� ������� � ���� �������
	int** a;
	a = A.getCopy();

	test_(a[0][0] == 0);
	test_(a[0][1] == 1);
	test_(a[0][2] == 2);
	test_(a[1][0] == 3);
	test_(a[1][1] == 4);
	test_(a[1][2] == 5);
	test_(a[2][0] == 6);
	test_(a[2][1] == 7);
	test_(a[2][2] == 8);


	// ��������� ����������
	Matrix<double> T;
	T = B.getPodmatrix(1, 1, 2, 2);

	test_(T[0][0] == 4);
	test_(T[0][1] == 5);
	test_(T[0][2] == 7);
	test_(T[1][0] == 8);
}

void TestMatrix::testOperators()
{
	// �������� ������������
	Matrix<int> E;
	E = A;
	test_(E.getN() == 3);
	test_(E.getM() == 3);

	test_(E[0][0] == 0);
	test_(E[0][1] == 1);
	test_(E[0][2] == 2);
	test_(E[1][0] == 3);
	test_(E[1][1] == 4);
	test_(E[1][2] == 5);
	test_(E[2][0] == 6);
	test_(E[2][1] == 7);
	test_(E[2][2] == 8);

	// �������� �����
	Matrix<double> Y(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Y[i][j] = 1;
		}
	}
	Y = Y + B;

	test_(Y.getN() == 3);
	test_(Y.getM() == 3);

	test_(Y[0][0] == 1);
	test_(Y[0][1] == 2);
	test_(Y[0][2] == 3);
	test_(Y[1][0] == 4);
	test_(Y[1][1] == 5);
	test_(Y[1][2] == 6);
	test_(Y[2][0] == 7);
	test_(Y[2][1] == 8);
	test_(Y[2][2] == 9);

	// �������� ������������
	Matrix<double> O(3, 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Y[i][j] = 0;
		}
	}

	O = Y * O;
	test_(O.getN() == 3);
	test_(O.getM() == 6);

	test_(O[0][0] == 0);
	test_(O[0][1] == 0);
	test_(O[0][2] == 0);

	// �������� ������������ �� �����
	Matrix<double> U(3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Y[i][j] = 1;
		}
	}
	U = U * 8;

	test_(U[0][0] == 8);
	test_(U[0][1] == 8);
	test_(U[0][2] == 8);
	test_(U[1][0] == 8);
	test_(U[1][1] == 8);
	test_(U[1][2] == 8);
	test_(U[2][0] == 8);
	test_(U[2][1] == 8);
	test_(U[2][2] == 8);

	U = 0 * U;

	test_(U[0][0] == 0);
	test_(U[0][1] == 0);
	test_(U[0][2] == 0);
	test_(U[1][0] == 0);
	test_(U[1][1] == 0);
	test_(U[1][2] == 0);
	test_(U[2][0] == 0);
	test_(U[2][1] == 0);
	test_(U[2][2] == 0);

	// �������� ����� ������� � �����
	Matrix<int> M;

	ofstream file;
	file.open("MatrixTest.txt");
	file << A;
	file.close();
	ifstream fileIn;
	fileIn.open("MatrixTest.txt");
	fileIn >> M;
	fileIn.close();

	test_(M.getN() == 3);
	test_(M.getM() == 3);

	test_(M[0][0] == 0);
	test_(M[0][1] == 1);
	test_(M[0][2] == 2);
	test_(M[1][0] == 3);
	test_(M[1][1] == 4);
	test_(M[1][2] == 5);
	test_(M[2][0] == 6);
	test_(M[2][1] == 7);
	test_(M[2][2] == 8);

	// �������� ����������
	test_(A[0][0] == 0);

	// �������� ��������� ������
	test_(E == A);
}

void TestMatrix::testExeptions()
{
	// ���������� � ������������ ��������������
	try {
		Matrix<int> t(-1, -2);
		fail_("�� �������� ���������� ��������� ������� �������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	double** t;
	t = new double*[2];
	t[0] = new double[2];
	t[1] = new double[2];

	try {
		Matrix<double> W(t, -1, -2);
		fail_("�� �������� ���������� ��������� ������� �������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	// ���������� � ������ ��������� ����������
	try {
		A.getPodmatrix(-1, 100, 2, 2);
		fail_("�� �������� ���������� ��������� ����������");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		A.getPodmatrix(1, 1, 3, 3);
		fail_("�� �������� ���������� ��������� ����������");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	// ���������� ��������� +
	try {
		Matrix<int> UU(1, 1);
		A + UU;
		fail_("�� �������� ���������� �������� ������ ������� �������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	// ���������� ��������� *
	try {
		Matrix<int> UUU(1, 1);
		A * UUU;
		fail_("�� �������� ���������� ��������� ������ ������� �������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	// ���������� ������ IsInRange
	try {
		A[10][10];
		fail_("�� �������� ���������� ������ �� ������� ������� �������!");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}
}

TestMatrix::~TestMatrix()
{
}
