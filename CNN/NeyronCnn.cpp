#include "NeyronCnn.h"



Neyron—nn::Neyron—nn() :  Matrix(), step(1)
{
}

Neyron—nn::Neyron—nn(const int & i_, const int & j_, const int& step_) : Matrix(i_,j_), step(step_)
{
}

Neyron—nn::Neyron—nn(int ** arr_, const int & i_, const int & j_, const int& step_) : Matrix(arr_, i_, j_), step(step_)
{
}

Neyron—nn::Neyron—nn(const Neyron—nn & copy) : Matrix(copy), step(1)
{
}

void Neyron—nn::Padding()
{
	n += 2;
	m += 2;
	int** copy;
	copy = new int*[n];
	for (int i = 0; i < n; i++) {
		copy[i] = new int[m];
	}
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m-1; j++) {
			copy[i][j] = arr[i-1][j-1];
		}
	}
	for (int i = 0; i < n - 2; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = copy;
}

void Neyron—nn::Svertka(Filter& F)
{
	int** rez;
	int n_out = (n - F.getN())/step+1;
	int m_out = (m - F.getM()) / step + 1;
	rez = new int*[n];

	for (int i = 0; i < n_out; i++) {
		rez[i] = new int[m_out];
	}
	
	int sum;
	int **fokus;

	for (int i = 0; i < n_out; i++) {
		for (int j = 0; j < m_out; j++) {
			sum = 0;
			fokus = getPodmatrix(i*step, j*step, F.getN(), F.getM());
			for (int ii = 0; ii < F.getN(); ii++) {
				for (int jj = 0; jj < F.getM(); jj++) {
					sum += fokus[ii][jj] * F[ii][jj];
				}
			}
			rez[i][j] = sum;
			delete fokus;
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	n = n_out;
	m = m_out;
	arr = rez;
}

Neyron—nn & Neyron—nn::operator=(const Neyron—nn & copy)
{
	if (&copy == this) {
		return *this;
	}
	Matrix::operator=(copy);
}

Neyron—nn::~Neyron—nn()
{
}

std::ostream & operator<<(std::ostream & out, const Neyron—nn & mat)
{
	out << (Matrix&)mat;
	out << mat.step;
	return out;
}

std::istream & operator>>(std::istream & out, Neyron—nn & mat)
{
	out >> ((Matrix&)mat);
	out >> mat.step;
	return out;
}
