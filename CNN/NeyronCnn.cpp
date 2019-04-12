#include "NeyronCnn.h"



NeyronÑnn::NeyronÑnn() :  Matrix(), step(1)
{
}

NeyronÑnn::NeyronÑnn(const int & i_, const int & j_, const int& step_) : Matrix(i_,j_), step(step_)
{
}

NeyronÑnn::NeyronÑnn(double ** arr_, const int & i_, const int & j_, const int& step_) : Matrix(arr_, i_, j_), step(step_)
{
}

NeyronÑnn::NeyronÑnn(const NeyronÑnn & copy) : Matrix(copy), step(1)
{
}

void NeyronÑnn::Padding()
{
	n += 2;
	m += 2;
	double** copy;
	copy = new double*[n];
	for (int i = 0; i < n; i++) {
		copy[i] = new double[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i == 0)||(j == 0)||(j == (m-1))||(i == (n-1))) {
				copy[i][j] = 0;
			}
			else {
				copy[i][j] = arr[i - 1][j - 1];
			}
		}
	}

	for (int i = 0; i < n - 2; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = copy;
}

void NeyronÑnn::Pooling(const int& n_, const int& m_)
{
	if ((n_ < 0) || (m_ < 0)||(n_ > n)||(m_ > m)) {
		throw NeyronÑnn::NeyronÑnnExeption("Íåâåğíûé ğàçìåğ ÿäğà!");
	}

	double** rez;
	int n_out = n / n_;
	int m_out = m / m_;

	rez = new double*[n_out];
	for (int i = 0; i < n_out; i++) {
		rez[i] = new double[m_out];
	}

	double **fokus;
	for (int i = 0; i < n_out; i++) {
		for (int j = 0; j < m_out; j++) {
			fokus = getPodmatrix(i*n_, j*m_, n_, m_);
			rez[i][j] = Matrix::Max(fokus, n_, m_);
			for (int i = 0; i < n_; i++) {
				delete[] fokus[i];
			}
			delete[] fokus;
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = rez;
	n = n_out;
	m = m_out;
}

void NeyronÑnn::Svertka(Filter& F)
{
	double** rez;
	int n_out = (n - F.getN())/step+1;
	int m_out = (m - F.getM()) / step + 1;
	rez = new double*[n];

	for (int i = 0; i < n_out; i++) {
		rez[i] = new double[m_out];
	}
	
	double sum;
	double **fokus;

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

NeyronÑnn & NeyronÑnn::operator=(const NeyronÑnn & copy)
{
	if (&copy == this) {
		return *this;
	}
	Matrix::operator=(copy);
	return *this;
}

NeyronÑnn::~NeyronÑnn()
{
}

std::ostream & operator<<(std::ostream & out, const NeyronÑnn & mat)
{
	out << (Matrix&)mat;
	out << mat.step;
	return out;
}

std::istream & operator>>(std::istream & out, NeyronÑnn & mat)
{
	out >> ((Matrix&)mat);
	out >> mat.step;
	return out;
}
