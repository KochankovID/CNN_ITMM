#include "TestMatrix.h"
#include <iostream>
#include <fstream>

using namespace std;

void TestMatrix::testConstruktors()
{
	double** a = new double*[2];
	a[0] = new double[4];
	a[1] = new double[4];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] = 3;
		}
	}
	Matrix h, b(5, 5), c(a, 2, 4);
	test_(h.getN() == 0);
	test_(h.getM() == 0);
	test_(h.asArray() == nullptr);
	test_(b.getN() == 5);
	test_(b.getM() == 5);
	test_(b[0][0] == 0);
	test_(c.getN() == 2);
	test_(c.getM() == 4);
	test_(c[0][0] == 3);
}

void TestMatrix::testMetods()
{
	test_(A.getN() == 3);
	test_(A.getM() == 3);
	double** a = new double*[2];
	a[0] = new double[4];
	a[1] = new double[4];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			a[i][j] = 3;
		}
	}

	Matrix b(a, 2, 4);
	test_(b.asArray()[1][3] == 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			B[i][j] = i;
		}
	}
	Matrix t = B.getPodmatrix(0, 0, 2, 2);

	test_(((t[0][0] == 0) || (t[0][1] == 0) || (t[1][0] == 1) || (t[1][1] == 1)));

	Matrix y = B.getPodmatrix(1, 1, 2, 2);

	test_(((y[0][0] == 1) || (y[0][1] == 1) || (y[1][0] == 2) || (y[1][1] == 2)));
	double** ff = y.getCopy();
	test_(ff[0][0] == 1);
	for (int i = 0; i < 2; i++) {
		delete[] ff[i];
	}
	delete[] ff;
	a[0][3] = 10;
	Matrix bb(a, 2, 4);
	test_(Matrix::Max(a, 2, 4)  == 10);
	test_(Matrix::Max(bb) == 10);
	
}

void TestMatrix::testOperators()
{
	Matrix a;
	a = A;
	test_(a.getN() == A.getN());
	test_(a.getM() == A.getM());
	test_(a[2][2] == A[2][2]);
	for (int i = 0; i < a.getN(); i++) {
		for (int j = 0; j < a.getM(); j++) {
			a[i][j] = 1;
		}
	}
	for (int i = 0; i < A.getN(); i++) {
		for (int j = 0; j < A.getM(); j++) {
			A[i][j] = 1;
		}
	}
	A = A + a;
	test_(A[0][0] == 2);
	A = A * A;
	test_(A[0][0] == 12);
	A = A * 2;
	test_(A[0][0] == 24);
	A = 2 * A;
	test_(A[0][0] == 48);

	ofstream file;
	file.open("MatrixText.txt");
	file << A;
	file.close();
	ifstream file1;
	file1.open("MatrixText.txt");
	file1 >> a;
	file1.close();
	test_(a[0][0] == 48);
	test_(A == a);

}

void TestMatrix::testExeptions()
{
	Matrix t(10, 10);

	try {
		t + B;
		fail_("Не вызванно исключение оператора +");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		B[5][1];
		fail_("Не вызванно исключение оператора []");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		B * t;
		fail_("Не вызванно исключение оператора *");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		B.getPodmatrix(-1,-2, 1, 1);
		fail_("Не вызванно исключение метода получение подматрицы *");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		B.getPodmatrix(1, 2, 10, 10);
		fail_("Не вызванно исключение метода получение подматрицы *");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

	try {
		Matrix t(-1, 5);
		fail_("Не вызванно исключение неверного размера матрицы");
	}
	catch (std::runtime_error& e) {
		succeed_();
	}

}

TestMatrix::~TestMatrix()
{
}
