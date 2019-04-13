#include <iostream>
#include "Matrix.h"

using namespace std;
Matrix::Matrix() : n(0), m(0)
{
	arr = nullptr;
}

Matrix::Matrix(double** arr_, const int& i, const int& j) : n(i), m(j)
{
	if ((n < 0) || (m < 0)) {
		throw Matrix::MatrixExeption("Неверный размер матрицы!");
	}
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = arr_[i][j];
		}
	}
}

Matrix::Matrix(const int& i, const int& j) : n(i), m(j)
{
	if ((n < 0) || (m < 0)) {
		throw Matrix::MatrixExeption("Неверный размер матрицы!");
	}
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix & copy) : n(copy.n), m(copy.m)
{
	initMat();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = copy.arr[i][j];
		}
	}
}

Matrix Matrix::getPodmatrix(const int& poz_n_, const int& poz_m_, const int& n_, const int& m_) {
	if ((poz_n_ < 0) || (poz_m_ < 0)) {
		throw Matrix::MatrixExeption("Неверная позиция верхнего левого элемента подматрицы!");
	}
	if (((poz_n_ + n_) > n) || ((poz_m_ + m_) > m)) {
		throw Matrix::MatrixExeption("Подматрица выходит за границы матрицы!");
	}

	Matrix rez(n_, m_);

	for (int i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			rez[i][j] = arr[poz_n_ + i][poz_m_ + j];
		}
	}
	return rez;
}

double Matrix::Max(double** arr_, const int& n_, const int& m_) {
	double max = arr_[0][0];
	for (int i = 0; i < n_; i++) {
		for (int j = 0; j < m_; j++) {
			if (arr_[i][j] > max) {
				max = arr_[i][j];
			}
		}
	}
	return max;
}

double Matrix::Max() {
	double max = arr[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}


double** Matrix::getCopy()
{
	double** copy;
	copy = new double*[n];
	for (int i = 0; i < n; i++) {
		copy[i] = new double[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			copy[i][j] = arr[i][j];
		}
	}
	return copy;
}


Matrix & Matrix::operator=(const Matrix & copy)
{
	if (this == &copy) {
		return *this;
	}
	if ((copy.n > n)||(copy.m > m)) {
		for (int i = 0; i < n; i++) {
			delete[] arr[i];
		}
		delete[] arr;
		n = copy.n;
		m = copy.m;
		initMat();
	}
	else {
		n = copy.n;
		m = copy.m;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = copy.arr[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix & mat) const
{
	Matrix tmp(*this);
	if ((n != mat.n)||(m != mat.m)) {
		throw MatrixExeption("Невозможно выполнить сложение матриц разного размера");
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j] += mat.arr[i][j];
		}
	}
	return tmp;
}

Matrix Matrix::operator*(const Matrix & mat) const
{
	if (m != mat.n) {
		throw MatrixExeption("Невозможно выполнить умножение матриц с несовпадающим количеством столбцов в первой и строк во второй");
	}
	Matrix tmp(n,mat.m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < mat.m; j++) {
			for (int o = 0; o < m; o++) {
				tmp[i][j] += arr[i][o] * mat.arr[o][j];
			}
		}
	}
	return tmp;
}

Matrix Matrix::operator*(const int k) const
{
	Matrix tmp(*this);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

double* Matrix::operator[](int index)
{
	isInRange(index);
	return arr[index];
}

const double* Matrix::operator[](int index) const
{
	isInRange(index);
	return arr[index];
}

bool Matrix::operator==(const Matrix & mat) const
{
	if ((n != mat.n)||(m != mat.m)) {
		return false;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] != mat.arr[i][j]) {
				return false;
			}
		}
	}
	return true;
}

Matrix::~Matrix()
{
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

void Matrix::initMat()
{
	arr = new double*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new double[m];
	}
}

void Matrix::isInRange(int index) const
{
	if ((index > n) || (index < 0)) {
		throw MatrixExeption("Индекс выходит за размер матрицы!");
	}
}

Matrix operator*(const int k, const Matrix & mat)
{
	Matrix tmp(mat);
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

ostream& operator<<(ostream& out, const Matrix& mat)
{
	out << mat.n << ' ' << mat.m << endl; // Для совместимости с вводом из файла

	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			out << mat.arr[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}

istream& operator>>(istream & in, Matrix & mat)
{
	in >> mat.n;
	in >> mat.m;
	if ((mat.n < 0) || (mat.m < 0)) {
		throw Matrix::MatrixExeption("Неверный размер матрицы!");
	}
	mat.initMat();
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			in >> mat.arr[i][j];
		}
	}
	return in;
}